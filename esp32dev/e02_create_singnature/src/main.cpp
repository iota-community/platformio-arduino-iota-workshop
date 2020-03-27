#include <Arduino.h>

#include "common/helpers/sign.h"
#include "common/model/transaction.h"
#include "common/trinary/tryte.h"

//Configuration
//Do not use this seed in production code!
//Best practice: Store the seed in a config file and read the config file. Even better: Encrypt the seed file.
char const *seed = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
char const *bundle_hash = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
int security_level = 2;

void setup() {
  //This code runs only once at the bootup of the device.
  Serial.begin(9600);
  Serial.println("Setup done.");
  Serial.print("Seed used in this example: ");
  Serial.println(seed);
}

int seed_index = 0;
unsigned long signature_gen_start;
unsigned long signature_gen_end;
void loop() {
  signature_gen_start = millis();
  //Create a signature. 2187 trytes for security level 1 and 4374 trytes for security level 2.
  //Read more about the transaction structure: https://docs.iota.org/docs/getting-started/0.1/transactions/transactions
  //and signatures: https://docs.iota.org/docs/getting-started/0.1/clients/addresses
  char * signature = iota_sign_signature_gen_trytes((char*)seed, seed_index, security_level, (char*)bundle_hash); 
  signature_gen_end = millis();

  Serial.println("\n");
  Serial.print("Signature for address with index ");
  Serial.print(seed_index);
  Serial.print(" and security level ");
  Serial.print(security_level);
  Serial.print(":");
  Serial.println(signature);

  free(signature);
  seed_index++;
  delay(500);
}
