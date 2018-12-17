#include <avr/io.h>
#include <stdlib.h>

#define BAUD_RATE 9600UL
#define F_CPU 8000000UL

#include <util/delay.h>

#include <avr/interrupt.h>

#include "oscilloscope.h"
#include "uart.h"

#define _CMD_START_CNT 1
#define _CMD_END_CNT   1
#define _CMD_SPACING   1
#define _CMD_PINS_ST   1
#define _CMD_TIME_SNAP 4

#define FULL_SAMPLE_CNT (_CMD_START_CNT + _CMD_PINS_ST +  _CMD_TIME_SNAP + _CMD_END_CNT)

#define _SAMPLE_PIN  (_CMD_START_CNT)
#define _SAMPLE_TIME (_CMD_START_CNT + _CMD_PINS_ST)

#define MARKER_END   (FULL_SAMPLE_CNT - 1)
#define MARKER_START (0)

// Send the following frame for each sample:
// @PIN TIME3 TIME2 TIME1 TIME0;

#define _SAMPLES_NUM 200

#define LOGIC_PORT PINB

typedef enum {SAMPLING, SENDING, IDLE} states_t;


//static logic_port_state = 0;
//static logic_port_pre_state;
static states_t currentState = SENDING;
static uint8_t  analog_samples[_SAMPLES_NUM];
static uint32_t time_snap[_SAMPLES_NUM];
static uint8_t cmd_buffer[FULL_SAMPLE_CNT];
static double timer = 0;

uint32_t getTime(void)
{
    // TODO: Place your code here, to compute the elapsed time.
	//double i=0.000128;
	/* Disable interrupts */
	cli();
	/* Read TCNT1 into i */
	timer++;
	TCNT1 = 0;
	TIFR |= (1<<OCF1A) ;
	/* Reactivate global interrupt */
	sei();
	/* calculate time */
	//Time = i*Time;
	return timer*15;
}

uint8_t getADCSample(void)
{
    double ADCvalue = 0;
    ADCSRA |= (1 << ADSC);
    while(!(ADCSRA & (1<<ADIF))); // waiting for ADIF, conversion complete
    ADCvalue = ADCH;
    return (((ADCvalue)*5)/256)*10;
}

void OSCI_Init(void)
{
    /* Init UART driver. */
    UART_cfg my_uart_cfg;
    
    /* Set USART mode. */
    my_uart_cfg.UBRRL_cfg = (BAUD_RATE_VALUE)&0x00FF;
    my_uart_cfg.UBRRH_cfg = (((BAUD_RATE_VALUE)&0xFF00)>>8);
    
    my_uart_cfg.UCSRA_cfg = 0;
    my_uart_cfg.UCSRB_cfg = (1<<RXEN)  | (1<<TXEN) | (1<<TXCIE) | (1<<RXCIE);
    my_uart_cfg.UCSRC_cfg = (1<<URSEL) | (3<<UCSZ0);
    
    UART_Init(&my_uart_cfg);
    
    
    // TODO: Place your code here for timer1 initialization to normal mode and keep track
    // to time elapsed.
	{
		cli();
		TCCR1A = 0;
		TCCR1B = 0;
		TCCR1B = (1<<CS12);
		OCR1A = 500;
		TCNT1 = 0;
		sei();
	}
    // Initialize ADC.
    {
        ADMUX = 0b01100000;    // PA0 -> ADC0, ADLAR=1 (8-bit)
        ADCSRA |= ((1<<ADEN) | (1<<ADSC) | (1<<ADPS1)); // ADC prescaler at 4
    }

    /* Clear cmd_buffer. */
    for(uint8_t i = 0; i < FULL_SAMPLE_CNT; i += 1) { cmd_buffer[i] = 0; }

    /* Start with analog sampling. */ 
    currentState = SAMPLING;    
}

void OSCI_MainFunction(void)
{    
    static volatile uint8_t samples_cnt = 0;
    static char _go_signal_buf = 'N';
    // Main function must have two states,
    // First state is command parsing and waveform selection.
    // second state is waveform executing.
    switch(currentState)
    {
        case SAMPLING:
        {
            // DO here sampling.
			while((TIFR & (1<<OCF1A)) == 0);
            analog_samples[samples_cnt] = getADCSample();
            time_snap[samples_cnt]      = getTime();
            
            // Increment sample count.
            samples_cnt++;

            // Start sending the collected _SAMPLES_NUM samples.
            currentState = (samples_cnt >= _SAMPLES_NUM) ? SENDING : SAMPLING;
            break;
        }
        case SENDING:
        {
            // For _SAMPLES_NUM samples send the construct the buffer.
            static uint8_t _sample_buf[FULL_SAMPLE_CNT];
            for(uint8_t i = 0; i < _SAMPLES_NUM; ++i)
            {
                // Construct the buffer._SAMPLES_NUM
                char S[3],S1[4];int nCh;
                // Add buffer marker
                _sample_buf[MARKER_START] = ',';

                // Add pin value.
				itoa(analog_samples[i],S,10);
				if (analog_samples[i]>=0){
					_sample_buf[_SAMPLE_PIN]  = S[0];
					_sample_buf[_SAMPLE_PIN+1]  = S[1];}
				else{
					_sample_buf[_SAMPLE_PIN]  = S[1];
					_sample_buf[_SAMPLE_PIN+1]  = S[2];}

                // Add time snap value.
				itoa(time_snap[i],S1,10);
				
				if (time_snap[i]>100)
					nCh = 4;
				else if (time_snap[i]<100)
					nCh = 3;
				else if (time_snap[i]>10)
					nCh = 2;
				else
					nCh = 1;

				for (int count=0;count<nCh;count++)
                _sample_buf[_SAMPLE_TIME + count+1] = (S1[count]);
				

                _sample_buf[MARKER_END+1]   = '\n';

                // Send sample.
                UART_SendPayload(_sample_buf, FULL_SAMPLE_CNT+1);
                while (0 == UART_IsTxComplete());
				_delay_ms(50);
            }

            // Trigger receiving for go signal.
            UART_ReceivePayload(&_go_signal_buf, 1);   
        }
        case IDLE:
        {
            currentState = SAMPLING;
			//((1 == UART_IsRxComplete())&&(_go_signal_buf == 'G')) ? SAMPLING : IDLE;
            if(currentState == SAMPLING)
            {
                _go_signal_buf = 'N';
                // TODO: Place your code here to reset the timer value.
				cli();
				TCNT1 = 0x00;
				sei();
            }

            break;
        }
        default: {/* Do nothing.*/}
    }
}

