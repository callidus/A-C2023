
#include <ctype.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct { long long int dst, src, len; } Range;

long long int got = 0;
long long int seeds[64];
Range seedToSoil[64];
Range soilToFert[64];
Range fertToWater[64];
Range waterToLight[64];
Range lightToTemp[64];
Range tempToHumid[64];
Range humidToLoc[64];

int numSeeds;
int nSeedToSoil;
int nSoilToFert;
int nFertToWater;
int nWaterToLight;
int nLightToTemp;
int nTempToHumid;
int nHumidToLoc;

int readRange(FILE* fp, Range* r) {
  int n = 0;
  while(fscanf(fp, "%lli %lli %lli\n", &r[n].dst, &r[n].src, &r[n].len) == 3) {
    n++;
  }
  return n;
}

void dump(Range* r, int n, const char* name) {
  printf("%s (%i)\n", name, n);
  for(int i=0; i<n; ++i) {
    printf("%lli %lli %lli\n", r[i].dst, r[i].src, r[i].len);
  }
  printf("\n");
}

long long int convertVal(long long int val, Range* r, long long int n) {
  long long int out = val;
  
  for(int i=0; i<n; ++i) {
    if( val >= r[i].src && val < (r[i].src + r[i].len) ) {
      out = r[i].dst + (val - r[i].src);
      break;
    }
  }
//  printf("-> %i ", out);
  return out;
}

long long int rconvertVal(long long int val, Range* r, long long int n) {
  long long int out = val;
  
  for(int i=0; i<n; ++i) {
    if( val >= r[i].dst && val < (r[i].dst + r[i].len) ) {
      out = r[i].src + (val - r[i].dst);
      break;
    }
  }
//  printf("-> %i ", out);
  return out;
}

long long int findLoc(long long int seed) {
  long long int val = seed;
  val = convertVal(val, seedToSoil, nSeedToSoil);
  val = convertVal(val, soilToFert, nSoilToFert);
  val = convertVal(val, fertToWater, nFertToWater);
  val = convertVal(val, waterToLight, nWaterToLight);
  val = convertVal(val, lightToTemp, nLightToTemp);
  val = convertVal(val, tempToHumid, nTempToHumid);
  val = convertVal(val, humidToLoc, nHumidToLoc);
  printf("\n");
  return val;
}

long long int rfindLoc(long long int seed) {
  long long int val = seed;
  
  //printf("%lli\n", val);
  val = rconvertVal(val, humidToLoc, nHumidToLoc);

  //printf("%lli\n", val);
  val = rconvertVal(val, tempToHumid, nTempToHumid);

  //printf("%lli\n", val);
  val = rconvertVal(val, lightToTemp, nLightToTemp);

  //printf("%lli\n", val);
  val = rconvertVal(val, waterToLight, nWaterToLight);

  //printf("%lli\n", val);
  val = rconvertVal(val, fertToWater, nFertToWater);

  //printf("%lli\n", val);
  val = rconvertVal(val, soilToFert, nSoilToFert);

  //printf("%lli\n", val);
  val = rconvertVal(val, seedToSoil, nSeedToSoil);
  
  //printf("\n");
  return val;
}


int main(int argc, char** argv) {
	FILE* fp = fopen("data.txt", "r");
  char nop[128];
  
  memset(seeds, 0, sizeof(int) * 64);
  memset(seedToSoil, 0, sizeof(Range) * 64);
  memset(soilToFert, 0, sizeof(Range) * 64);
  memset(fertToWater, 0, sizeof(Range) * 64);
  memset(waterToLight, 0, sizeof(Range) * 64);
  memset(lightToTemp, 0, sizeof(Range) * 64);
  memset(tempToHumid, 0, sizeof(Range) * 64);
  memset(humidToLoc, 0, sizeof(Range) * 64);

  numSeeds = 0;
  fscanf(fp, "seeds: ");
  while(fscanf(fp, "%lli", &seeds[numSeeds++]));
  for(int i=0; i<numSeeds; ++i) printf("%lli,", seeds[i]);	
  printf("\n");	
    
  fscanf(fp,"seed-to-soil map:\n");
  nSeedToSoil = readRange(fp, seedToSoil);
  dump(seedToSoil, nSeedToSoil, "Seed to Soil");

  fscanf(fp,"soil-to-fertilizer map:\n");
  nSoilToFert = readRange(fp, soilToFert);
  dump(soilToFert, nSeedToSoil, "Soil to Fert");
  
  fscanf(fp,"fertilizer-to-water map:\n");
  nFertToWater = readRange(fp, fertToWater);
  dump(fertToWater, nFertToWater, "Fert to Water");
  
  fscanf(fp,"water-to-light map:\n");
  nWaterToLight = readRange(fp, waterToLight);
  dump(waterToLight, nWaterToLight, "Water to Light");
  
  fscanf(fp,"light-to-temperature map:\n");
  nLightToTemp = readRange(fp, lightToTemp);
  dump(lightToTemp, nLightToTemp, "Light to Temp");
  
  fscanf(fp,"temperature-to-humidity map:\n");
  nTempToHumid = readRange(fp, tempToHumid);
  dump(tempToHumid, nTempToHumid, "Temp to Humid");
  
  fscanf(fp,"humidity-to-location map:\n");
  nHumidToLoc = readRange(fp, humidToLoc);
  dump(humidToLoc, nHumidToLoc, "Humid to Loc");

/*
  got = INT_MAX;
  for(int i=0; i<numSeeds - 1; ++i) {
    long long int v = findLoc(seeds[i]);
    printf("%lli loc %lli\n", seeds[i], v);	
    got = v < got ? v : got;
  }
*/

  Range seedRanges[1024];
  for(int i=0; i<numSeeds/2; ++i) {
    seedRanges[i].src = seeds[i*2];
    seedRanges[i].len = seeds[i*2 + 1];
    printf("seed {%lli %lli}\n", seedRanges[i].src, seedRanges[i].len);
  }
  numSeeds /= 2;



  long long int i = 0;
  long long int v = 0;
  int ok = 0;
  while(!ok) {
    v = rfindLoc(i);
    i++;

    for(int j=0; j<numSeeds; ++j) {
      long long int e = seedRanges[j].src + seedRanges[j].len;
      if(v >= seedRanges[j].src && v < e) {
        printf("ok");
        ok = 1;
      }
    }
  }

  printf("got %lli (%lli)\n", i-1, v);
  return 0;
}


