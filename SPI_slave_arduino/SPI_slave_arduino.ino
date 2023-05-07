#include <SPI.h>

char buf [100];//Definimos el arreglo de caracteres que será nuestro buffer de recepción 
volatile byte pos; //Indice auxiliar para administrar el índice del arreglo "buf"
volatile boolean process_it;  //Bandera auxiliar para saber cuando hemos recibido un comando 
char on[] = {111,110,10};   //Arreglo de carácteres correspondientes a la cadena "on\n"
char off[] = {111,102,102,10}; //Arreglo de carácteres correspondientes a la cadena "off\n"
int pin_led = 14; //Pin al cual se conecto la señal del led

void setup (void)
{
  Serial.begin (9600);   
  pinMode(pin_led, OUTPUT);
  
  // Configuramos como salida el pin correspondiente a la salida de datos por parte del esclavo
  pinMode(MISO, OUTPUT);
  
  // Establecemos el modo de esclavo
  SPCR |= _BV(SPE);
 
  pos = 0;             // buffer vacio
  process_it = false;  //bandera auxiliar para indicar cuando un comando completo se encuentra en buffer

  // Habilitamos interrupciones por SPI
  SPI.attachInterrupt();

}  // fin de setup


// Rutina de interrupción SPI
ISR (SPI_STC_vect)
{
   byte c = SPDR;  // tomamos el byterecibido que se encuentra en el registro de datos SPI
  
  //si contamos con espacio agregamos el byte a la cadena de caracteres
  if (pos < sizeof buf)
    {
    buf [pos++] = c; //Agregamos el caracter recibido 
    
    // Si el caracter actual es un salto de línea sabemos que hemos recibido un comando completo 
    if (c == '\n')
      process_it = true;//Levantamos la bandera
      
    }  
}  // fin de la rutina de interupción SPI

void loop (void)
{
  if (process_it)//Si la bandera esta levantada procesamos el comando recibido
    {
    if(array_cmp(on,buf,3,pos)) digitalWrite(pin_led, 1);
    if(array_cmp(off,buf,4,pos)) digitalWrite(pin_led, 0);
    pos = 0;
    process_it = false;
    }  // fin del procesamiento del comando recibido
    
}  // fin del loop


boolean array_cmp(char *a, char *b, int len_a, int len_b){
     int n;

     // Si la longitud es distinta regresa FALSO y terminamos la función
     if (len_a != len_b) return false;

     // Comparramos pares de bytes formados por los los elementos que tienen el mismo índice en sus respectivos arreglos
     //Si algún par está formado por bytes distintos, regresa FALSO y termina la función
     for (n=0;n<len_a;n++) if (a[n]!=b[n]) return false;

     //Si llegamos hast aqui es porque los arreglos son identicos
     return true;
}//fin de la función