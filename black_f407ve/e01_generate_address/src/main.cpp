#include <Arduino.h>

#include "common/helpers/sign.h"
#include "common/model/transaction.h"
#include "common/trinary/tryte.h"

//Configuration
//Do not use this seed in production code!
//Best practice: Store the seed in a config file and read the config file. Even better: Encrypt the seed config file.
//Todo: Use integrated sd card slot to store seed
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
unsigned long addr_gen_start;
unsigned long addr_gen_end;
void loop() {
  addr_gen_start = millis();
  //Generate a IOTA address (81 trytes)
  //Read more about it: https://docs.iota.org/docs/getting-started/0.1/clients/addresses
  char *addr = iota_sign_address_gen_trytes(seed, seed_index, security_level);
  addr_gen_end = millis();

  Serial.print("Address from seed index ");
  Serial.print(seed_index);
  Serial.print(" with security level ");
  Serial.print(security_level);
  Serial.print(":");
  Serial.println(addr);

  Serial.print("Generating address took: ");
  Serial.print(addr_gen_end-addr_gen_start);
  Serial.println(" ms");

  free(addr);
  seed_index++;
  delay(500);
}
