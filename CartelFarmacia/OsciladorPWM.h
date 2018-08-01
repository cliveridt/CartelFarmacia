class osciladorPWM
{
	public:
	int t0,t1,t2,t3,t4;	//tiempos que separan las secuencias
	int t=0;		//Variable
	float PWM_MAX;	
	unsigned char pin;
	
	/* Esta clase genera una señal oscilante con un maximo PWM_MAX. Los tiempos que se introducen en el constructor son los deltas entre los tiempos t0,t1,...
	          ________ 
	|        /        \_
	|       /           \_
	|      /              \_
	|     /        	        \
	|----|---|--------|------|-------|--
	   t0   t1       t2     t3      t4  
     <-------------T---------------->
	*/
	//El constructor no es void, y tiene que tener si o si el mismo nombre que la clase
	osciladorPWM(unsigned char salida, int maximo,  int dt0,  int dt1,  int dt2,  int dt3,  int dt4){
		pin = salida;
		pinMode(pin,OUTPUT);
		PWM_MAX = maximo;
		
		t0=dt0;
		t1=t0+dt1;
		t2=t1+dt2;
		t3=t2+dt3;
		t4=t3+dt4;
		t=0;
		
		
		
	}
	
	void oscilar(){
		t++;
		analogWrite(pin,funcion());
		if (t>t4){
			t=0;
		}
	}
	
	unsigned char funcion(){
		if (t<=t0){
			return 0;
		}
		else if(t>t0 && t<=t1){
			float aux = (PWM_MAX / (t1-t0)) * (t-t0);
			return (unsigned char)aux;
		}
		else if(t>t1 && t<=t2){
			return PWM_MAX;
		}
		else if(t>t2 && t<=t3){
			float aux = (PWM_MAX * (t-t3)) / (t2-t3);
			return (unsigned char)aux;
		}
		else if(t>t3){
			return 0;
		}
	}
};
