/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include "Corazon.h"
#include "OsciladorPWM.h"
/*End of auto generated code by Atmel studio */



unsigned char modo;
unsigned char enturno=0;
unsigned int tiempo=0,automatico=0;
unsigned int t_auto=0;	//Este tiempo es para cambiar el modo cuando automatico=1

/*Control remoto
	A=D2
	B=D0
	C=D3
	D=D1
*/

#define CANT_MODOS 9
//Salidas
const int cruz1 = 5;	// Cruz interna (OC0B)
const int cruz2 = 6;	// Cruz externa (OC0A)
const int circ	= 3;	// Circunferencia externa (OC2B)
const int turno = 11;	// Mensaje "de turno" (OC2A)

//Entradas
const int D0 = 14;	//DataIn0	(A0)
const int D1 = 15;	//DataIn1	(A1)
const int D2 = 16;	//DataIn2	(A2)
const int D3 = 17;	//DataIn3	(A3)


//Modo 4
corazon latido4a = corazon(cruz1,0,20,20,10,40,40);
corazon latido4b = corazon(cruz2,10,20,20,10,40,30);
corazon latido4c = corazon(circ,60,30,30,0,0,10);

//Modo 5
osciladorPWM PWM5a = osciladorPWM(cruz1,255,0,40,0,40,160);
osciladorPWM PWM5b = osciladorPWM(cruz2,255,80,40,0,40,80);
osciladorPWM PWM5c = osciladorPWM(circ,255,160,40,0,40,0);

//Modo 6
osciladorPWM PWM6a = osciladorPWM(cruz1,255,0,40,20,40,80);
osciladorPWM PWM6b = osciladorPWM(cruz2,255,40,40,20,40,40);
osciladorPWM PWM6c = osciladorPWM(circ,255,80,40,20,40,0);

//osciladorPWM PWM6a = osciladorPWM(cruz1,255,0,40,20,40,1600);	//Esta combinacion da una aleatoriedad muy copada! xD
//osciladorPWM PWM6b = osciladorPWM(cruz2,255,40,40,20,40,80);
//osciladorPWM PWM6c = osciladorPWM(circ,255,80,40,20,40,0);

//Modo 7
osciladorPWM PWM7a = osciladorPWM(cruz1,255,0,40,20,40,40);
osciladorPWM PWM7b = osciladorPWM(cruz2,255,0,40,20,40,40);
osciladorPWM PWM7c = osciladorPWM(circ,255,0,40,20,40,40);

//En turno
osciladorPWM TURNO = osciladorPWM(turno,255,0,100,100,100,100);


ISR (PCINT1_vect) // Interrupciones por cambio en las entradas del control remoto
{
	delay(500);		//Antirrebote
	if(digitalRead(D0)==1){	//D0 cambia el modo al siguiente
		automatico=0;
		modo++;
		if(modo>CANT_MODOS){modo=0;}
		while(digitalRead(D0));	//Espera a que se suelte el boton
		//PCIFR=0;				//Limpia la bandera para no volver a entrar en la interrupcion
	}
	else if(digitalRead(D2)==1){	//D2 cambia el modo hacia atras
		automatico=0;		
		modo--;
		if (modo==255){modo=CANT_MODOS;}
		while(digitalRead(D2));	//Espera a que se suelte el boton
		//PCIFR=0;				//Limpia la bandera para no volver a entrar en la interrupcion
	}
	else if(digitalRead(D1)==1){	//D1 enciende el mensaje "En turno"
		enturno=1;
		while(digitalRead(D1));	//Espera a que se suelte el boton
		//PCIFR=0;				//Limpia la bandera para no volver a entrar en la interrupcion
	}
	else if(digitalRead(D3)==1){	//D3 apaga el mensaje "En turno"
		enturno=0;
		digitalWrite(turno,LOW);
		while(digitalRead(D3));	//Espera a que se suelte el boton
		//PCIFR=0;				//Limpia la bandera para no volver a entrar en la interrupcion
	}

}

ISR(TIMER1_OVF_vect){
	TCNT1 = 0xB1E0;		//Precarga para que desborde en 10ms
	t_auto++;			//Cuenta las veces que desbordo para cambiar el modo cuando esta en automatico
	if(t_auto>5000 && automatico==1){
		modo++;
		if(modo>CANT_MODOS){modo=0;}
		t_auto=0;	
	}
	if(modo==6){
		latido4a.latir();
		latido4b.latir();
		latido4c.latir();
	}
	if(modo==7){
		PWM5a.oscilar();
		PWM5b.oscilar();
		PWM5c.oscilar();
	}
	if(modo==8){
		PWM6a.oscilar();
		PWM6b.oscilar();
		PWM6c.oscilar();
	}
	if(modo==9){
		PWM7a.oscilar();
		PWM7b.oscilar();
		//PWM7c.oscilar();
		digitalWrite(circ,HIGH);
	}
	if(enturno==1){
		TURNO.oscilar();
	}

}



void setup() {
	//GPIO
	pinMode(cruz1,OUTPUT);
	pinMode(cruz2,OUTPUT);
	pinMode(circ,OUTPUT);
	pinMode(turno,OUTPUT);
	
	pinMode(D0,INPUT);
	pinMode(D1,INPUT);
	pinMode(D2,INPUT);
	pinMode(D3,INPUT);
	
	//Interrupciones
	PCIFR = 0;	//Baja todas las banderas de interrupcion
	PCICR = 0x02;	//Habilita las interrupciones por cambio desde A0 a A5
	PCMSK1 = 0x0F;	//Habilita las interrupciones de A0:A4
	
	//Timers
	TCCR1A = 0;	//NO comienza necesariamente en cero al encender/reiniciar el micro
	TCCR1B = 0x02;	//Prescaler 1:8
	TIMSK1 = 0x01;	//Interrupcion por overflow
	
	
	digitalWrite(cruz1,LOW);
	digitalWrite(cruz2,LOW);
	digitalWrite(circ,LOW);
	digitalWrite(turno,LOW);
}

void loop() {
	switch(modo){
		case 0:
			digitalWrite(circ,HIGH);
			digitalWrite(cruz1,HIGH);
			digitalWrite(cruz2,HIGH);
		break;
		
		case 1:
			digitalWrite(cruz1,HIGH);
			delay(500);
			digitalWrite(cruz2,HIGH);
			delay(500);
			digitalWrite(circ,HIGH);
			delay(500);
		
			digitalWrite(cruz1,LOW);
			delay(500);
			digitalWrite(cruz2,LOW);
			delay(500);
			digitalWrite(circ,LOW);
			delay(500);
			break;
		
		case 2:
			digitalWrite(cruz1,HIGH);
			delay(200);
			digitalWrite(cruz2,HIGH);
			delay(200);
			digitalWrite(circ,HIGH);
			delay(200);
		
			digitalWrite(cruz1,LOW);
			delay(200);
			digitalWrite(cruz2,LOW);
			delay(200);
			digitalWrite(circ,LOW);
			delay(200);
			break;

		case 3:
			digitalWrite(cruz1,HIGH);
			digitalWrite(cruz2,HIGH);
			digitalWrite(circ,HIGH);
			delay(200);
			digitalWrite(cruz1,LOW);
			delay(200);
			break;

		case 4:
			digitalWrite(cruz1,HIGH);
			digitalWrite(cruz2,HIGH);
			digitalWrite(circ,HIGH);
			delay(200);
			digitalWrite(cruz2,LOW);
			delay(200);
			break;

		case 5:
			digitalWrite(circ,HIGH);
			digitalWrite(cruz1,HIGH);
			digitalWrite(cruz2,HIGH);
			delay(500);
			
			digitalWrite(cruz1,LOW);
			digitalWrite(cruz2,LOW);
			delay(500);
			break;
		
		
		
		default:
		break;
	}

}
