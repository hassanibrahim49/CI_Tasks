
#define BAUD_RATE 9600

#include <avr/io.h>
#include <stdlib.h>

#include <util/delay.h>

#include "waveform.h"
#include "uart.h"

#define _CMD_START_CNT 1
#define _CMD_END_CNT   1
#define _CMD_WAVE_CNT  1
#define _CMD_AMP_CNT   3
#define _CMD_FRQ_CNT   3

#define FULL_CMD_CNT (_CMD_START_CNT +  _CMD_WAVE_CNT + _CMD_AMP_CNT + _CMD_FRQ_CNT + _CMD_END_CNT)
#define WAVE_OFFSET  (_CMD_START_CNT)
#define AMP_OFFSET   (_CMD_START_CNT +  _CMD_WAVE_CNT)
#define FREQ_OFFSET  (_CMD_START_CNT +  _CMD_WAVE_CNT + _CMD_AMP_CNT)
#define MARKER_END   (_CMD_START_CNT +  _CMD_WAVE_CNT + _CMD_AMP_CNT + _CMD_FRQ_CNT)
#define MARKER_START (0)

#define WAVEFORM_NUM 4

#define DAC_DDR  DDRB
#define DAC_PORT PORTB

// table of 256 sine values / one sine period / stored in flash memory
const unsigned char sine256[]  = {
  127,130,133,136,139,143,146,149,152,155,158,161,164,167,170,173,176,178,181,184,187,190,192,195,198,200,203,205,208,210,212,215,217,219,221,223,225,227,229,231,233,234,236,238,239,240,
  242,243,244,245,247,248,249,249,250,251,252,252,253,253,253,254,254,254,254,254,254,254,253,253,253,252,252,251,250,249,249,248,247,245,244,243,242,240,239,238,236,234,233,231,229,227,225,223,
  221,219,217,215,212,210,208,205,203,200,198,195,192,190,187,184,181,178,176,173,170,167,164,161,158,155,152,149,146,143,139,136,133,130,127,124,121,118,115,111,108,105,102,99,96,93,90,87,84,81,78,
  76,73,70,67,64,62,59,56,54,51,49,46,44,42,39,37,35,33,31,29,27,25,23,21,20,18,16,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,16,18,20,21,23,25,27,29,31,
  33,35,37,39,42,44,46,49,51,54,56,59,62,64,67,70,73,76,78,81,84,87,90,93,96,99,102,105,108,111,115,118,121,124

};

typedef enum {GENERATE_WAVE, UPDATE_WAVE} states_t;

static uint8_t cmd_buffer[FULL_CMD_CNT];
static void (*waveform[WAVEFORM_NUM])(uint8_t amp, uint8_t freq);
static states_t currentState = GENERATE_WAVE;
static uint8_t amp_value = 0;
static uint8_t freq_value = 0;
static uint8_t waveform_index = WAVEFORM_NUM;


void squareWave(uint8_t amp, uint8_t freq)
{
	// Refresh DAC DDR to be output.
    DAC_DDR = 255;
	
	int delay_time = -2 * (int) freq + 1000; 
	
    DAC_PORT = 0x00;
    _delay_us(delay_time);
    DAC_PORT = amp;
    _delay_us(delay_time);
}

void staircaseWave(uint8_t amp, uint8_t freq)
{
    // Refresh DAC DDR to be output.
    DAC_DDR = 255;

    // Generate waveform.
    DAC_PORT = 0x00;
    _delay_us(200);
    DAC_PORT = 0x33;
    _delay_us(200);
    DAC_PORT = 0x66;
    _delay_us(200);
    DAC_PORT = 0x99;
    _delay_us(200);
    DAC_PORT = 0xCC;
    _delay_us(200);
    DAC_PORT = 0xFF;
    _delay_us(200);
}

void triangleWave(uint8_t amp, uint8_t freq)
{
    // Refresh DAC DDR to be output.
    DAC_DDR = 255;
	
	for(uint8_t i = 0; i<=255; i++)
	{
		DAC_PORT = i;
        _delay_us(1000);
	}
	
	for(uint8_t i = 255; i>=0; i--)
	{
		DAC_PORT = i;
        _delay_us(1000);
	}
	
}

void sineWave(uint8_t amp, uint8_t freq)
{
    // Refresh DAC DDR to be output.
    DAC_DDR = 255;
	
	for(uint8_t i = 0; i<=255; i++)
	{
		DAC_PORT = sine256[i];
        _delay_us(10);
	}
}

void WAVE_Init(void)
{
    uint8_t i;
    
    /* Init UART driver. */
    UART_cfg my_uart_cfg;
    
    /* Set USART mode. */
    my_uart_cfg.UBRRL_cfg = (BAUD_RATE_VALUE)&0x00FF;
    my_uart_cfg.UBRRH_cfg = (((BAUD_RATE_VALUE)&0xFF00)>>8);
    
    my_uart_cfg.UCSRA_cfg = 0;
    my_uart_cfg.UCSRB_cfg = (1<<RXEN)  | (1<<TXEN) | (1<<TXCIE) | (1<<RXCIE);
    my_uart_cfg.UCSRC_cfg = (1<<URSEL) | (3<<UCSZ0);
    
    UART_Init(&my_uart_cfg);
    
    
    /* Clear cmd_buffer. */
    for(i = 0; i < FULL_CMD_CNT; i += 1)
    {
        cmd_buffer[i] = 0;
    }
    
    /* Initialize waveform array. */
    waveform[0] = squareWave;
    waveform[1] = staircaseWave;
    waveform[2] = triangleWave;
    waveform[3] = sineWave;

    /* Start with getting which wave to generate. */ 
    currentState = UPDATE_WAVE;    
}

void WAVE_MainFunction(void)
{    

    // Main function must have two states,
    // First state is command parsing and waveform selection.
    // second state is waveform executing.
    switch(currentState)
    {
        case UPDATE_WAVE:
        {
            UART_SendPayload((uint8_t *)">", 1);
            while (0 == UART_IsTxComplete());

            /* Receive the full buffer command. */
            UART_ReceivePayload(cmd_buffer, FULL_CMD_CNT);
            
            /* Pull unitl reception is complete. */
            while(0 == UART_IsRxComplete());

            /* Check if the cmd is valid. */
            if((cmd_buffer[MARKER_START] == '@') && (cmd_buffer[MARKER_END] == ';'))
            {
                // Extract amplitude and freq values before sending them to the waveform generator.
                /* Compute amplitude. */
                {
                    char _buffer[_CMD_AMP_CNT];
                    for(uint8_t i = 0; i < _CMD_AMP_CNT; ++i) { _buffer[i] = cmd_buffer[AMP_OFFSET+i]; }
                    amp_value = atoi(_buffer);
                }

                /* Compute frequency. */
                {
                    char _buffer[_CMD_FRQ_CNT];
                    for(uint8_t i = 0; i < _CMD_FRQ_CNT; ++i) { _buffer[i] = cmd_buffer[FREQ_OFFSET+i]; }
                    freq_value = atoi(_buffer);
                }

                /* Compute waveform. */
                {
                    waveform_index = cmd_buffer[WAVE_OFFSET] - '0';
                }
            } 
            else
            {
               /* Clear cmd_buffer. */
                for(uint8_t i = 0; i < FULL_CMD_CNT; i += 1)
                {
                    cmd_buffer[i] = 0;
                }
            }

            // Trigger a new reception.
            UART_ReceivePayload(cmd_buffer, FULL_CMD_CNT);

            UART_SendPayload((uint8_t *)"\r>", 2);
            while (0 == UART_IsTxComplete());
        }
        case GENERATE_WAVE:
        {
            // Execute waveform..
            if(waveform_index < WAVEFORM_NUM)
            {
                waveform[waveform_index](amp_value, freq_value);
            }
            // Keep in generate wave if no command it received.
            currentState = (1 == UART_IsRxComplete()) ? UPDATE_WAVE : GENERATE_WAVE;
            break;
        }
        default: {/* Do nothing.*/}
    }
}

