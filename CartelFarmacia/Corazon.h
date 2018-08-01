class corazon
{
	public:
	int t0,t1,t2,t3,t4,t5;	//tiempos que separan las secuencias
	int t=0;	//Variable
	unsigned char pin;
	
	/* Esta clase genera una señal de dos picos, que es periodica. Los tiempos que se introducen en el constructor son los deltas entre los tiempos t0,t1,...
	|        /\      /\_
	|       /  \    /   \_
	|      /    \  /      \_
	|     /      \/	        \
	|----|----|---|--|------|-------|--
	   t0   t1  t2 t3     t4      t5
     <-------------T---------------->
	*/
	//El constructor no es void, y tiene que tener si o si el mismo nombre que la clase
	corazon(unsigned char salida, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f){
		pin = salida;
		pinMode(pin,OUTPUT);
		t0=a;
		t1=t0+b;
		t2=t1+c;
		t3=t2+d;
		t4=t3+e;
		t5=t4+f;	//t5=periodo
		t=0;
	}
	
	void latir(){
		t++;
		analogWrite(pin,funcion());
		if (t>t5){
			t=0;
		}
	}
	
	unsigned char funcion(){
		if (t<=t0){
			return 0;
		}
		if(t>t0 && t<=t1){
			int aux = (255 / (t1-t0));
			return aux*(t-t0);
		}
		if(t>t1 && t<=t2){
			int aux = (255 / (t1-t2));
			return aux*(t-t2);
		}
		if(t>t2 && t<=t3){
			int aux = (255 / (t3-t2));
			return aux*(t-t2);
		}
		if(t>t3 && t<=t4){
			int aux = (255 / (t3-t4));
			return aux*(t-t4);
		}
		if(t>t4){
			return 0;
		}
	}
};
