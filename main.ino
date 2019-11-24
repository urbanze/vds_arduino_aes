#include <AES.h>//Biblioteca do AES.

AES aes;//Cria a classe aes.
byte key[16], out[16], inp[32];//Cria arrays (vetores) para a chave, input e output de dados.
const char pass[] = "abc";//Define a chave usada, neste exemplo usamos AES128, então precisa ser <= 16 Bytes.


void setup()
{
   Serial.begin(115200);//Habilita a serial.
   Serial.println();//Limpa o monitor.

   enc128("vida de silicio", 1);//Faz a função de encriptação e retorna o HEX encriptado.
}

void loop()
{

}


void enc128(const char txt[], bool db)//Argumentos: (texto e debug)
{
   if (strlen(pass) > 16)//Verifica se a chave tem o tamanho limite de 16 caracteres.
   {
      if (db == true)
      {
         Serial.println("Chave para AES128 <= 16 Bytes");
      }
      return;//Se a chave for maior, irá sair da função.
   }

   if (strlen(txt) > 16)//Verifica se o texto tem o tamanho limite de 16 caracteres.
   {
      if (db == true)
      {
         Serial.println("Frase/numero para AES <= 16 Bytes / bloco");
      }
      return;//Se o texto for maior, irá sair da função.
   }

   for (byte i = 0; i < strlen(pass); i++)//Adiciona a chave(pass) na array key.
   {
      key[i] = pass[i];
   }

   for (byte i = 0; i < strlen(txt); i++)//Adiciona o texto na array input.
   {
      inp[i] = txt[i];
   }

   //Adiciona a chave ao algoritimo.
   if (aes.set_key(key, 16) != 0)//Verifica se a chave esta correta, caso nao, sairá da função.
   {
      if (db == true)
      {
         Serial.println("Erro ao configurar chave");
      }
      return;//Sai da função
   }

   //Faz a encriptação da array INPUT e retorna o HEXA na array OUTPUT.
   if (aes.encrypt(inp, out) != 0)//Verifica se a encriptação esta correta, se não, sairá da função.
   {
      if (db == true)
      {
         Serial.println("Erro ao encriptar");
      }
      return;//Sai da função
   }

   if (db == true)//Se o debug estiver on (1), irá mostrar o HEXA no serial monitor.
   {
      for (byte i = 0; i < 16; i++)
      {
         Serial.print(out[i], HEX);
         Serial.print(" ");
      }
      Serial.println();
   }

   aes.clean();//Limpa a chave e residuos sensiveis da encriptação.
}
