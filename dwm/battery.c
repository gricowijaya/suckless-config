/*
Copyright (c) 2012, Daniel Bugl
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Daniel Bugl nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL DANIEL BUGL BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Usage example:
xsetroot -name "`battery` | `date +%R`"
(Put this into your .xinitrc, for example)
*/

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv) {
 int ac_online;
 float energy_now, energy_full, current_now, current_avg;
 char cfavg[64];
 FILE *ac, *enow, *efull, *cnow, *cavg;
 
 ac = fopen("/sys/class/power_supply/ADP0/online","r");
 if(ac != NULL) fscanf(ac,"%i",&ac_online);
 fclose(ac);
 
 if(ac_online == 1) printf("(+)");
 else printf("(-)");
 
 enow = fopen("/sys/class/power_supply/BAT0/charge_now","r");
 if(enow != NULL) fscanf(enow,"%f",&energy_now);
 fclose(enow);
 
 efull = fopen("/sys/class/power_supply/BAT0/charge_full","r");
 if(efull != NULL) fscanf(efull,"%f",&energy_full);
 fclose(efull);
 
 cnow = fopen("/sys/class/power_supply/BAT0/voltage_now","r");
 if(cnow != NULL) fscanf(cnow,"%f",&current_now);
 fclose(cnow);
 
 sprintf(cfavg, "%s/.BAT0_current_avg", getenv("HOME"));
 if((cavg = fopen(cfavg,"r+")) == NULL) cavg = fopen(cfavg,"w");
 if(cavg != NULL) fscanf(cavg,"%f",&current_avg);
 fclose(cavg);
 current_avg = (2 * current_avg + current_now) / 3;
 cavg = fopen(cfavg,"w");
 fprintf(cavg, "%.0f\n", current_avg);
 fclose(cavg);
 
 if(current_now > 0 && ac_online != 1)
  printf("%.0f\'%i\" ", energy_now/current_avg, (int)(60*energy_now/current_avg) % 60);
 printf("%.0f%%\n",100*energy_now/energy_full);
 
 return 0;
}