const int ledPin = 13; // cria uma constante com o numero do pino ligado ao LED
const int btnDesPin = 2; 
const int btnAcePin = 3;

float timerange = 1000;
int now;
int before;
int ledState = LOW;

int click1_now;
int click1_before;

int click2_now;
int click2_before;

int val;

void setup()
{
  pinMode(ledPin, OUTPUT); // declara o pino do led como saída
  pinMode(btnDesPin, INPUT); // declara o pino do botao como entrada
  pinMode(btnAcePin, INPUT);
}
 
void loop()
{
  val = digitalRead(btnDesPin); // le o valor na entrada
  if (val == LOW) // se valor está em zero( tecla pressionada)
  {
    click1_before = click1_now;
    click1_now = millis();
    if (click1_now-click1_before >=100){ //para corrigir problema de estabilizacao
   		 timerange = timerange*1.2; //Diminui tempo do pisca-pisca em 20%
    }
   
    
  }
  val = digitalRead(btnAcePin);
   if (val == LOW)
  {
    click2_before = click2_now;
    click2_now = millis();
    if (click2_now-click2_before >=100){
    	timerange = timerange*0.8; //Aumenta tempo do pisca-pisca em 20%
    }
  }
  
  //verifica se o tempo entre os 2 cliques esta dentro da condicao de parada
  if ((click1_now-click2_now <= 500 && click1_now>click2_now)||(click2_now-click1_now <= 500 && click2_now>click1_now)){
    digitalWrite(ledPin, LOW);
    while(1){
      
      /*Se um dos botoes forem pressionados,
      o tempo do pisca-pisca reseta e o mesmo
      volta a piscar*/
      
     val =  digitalRead(btnAcePin);
      if (val == LOW){
       timerange = 1000;
        break;
      }
      val =  digitalRead(btnDesPin);
      if (val == LOW){
       timerange = 1000;
        break;
      }
    }
  }
	now = millis();
   if (now - before > timerange) {
    ledState = !ledState;
    
    digitalWrite(ledPin, ledState);
    before = now;
  }
}
