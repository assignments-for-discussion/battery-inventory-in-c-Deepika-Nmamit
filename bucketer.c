#include <stdio.h>
#include <assert.h>

struct CountsBySoH {
  int healthy;
  int exchange;
  int failed;
};

double calculateSoH(int presentCapacity, int ratedCapacity) {
  return (double)presentCapacity / ratedCapacity * 100.0;
}

struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
  struct CountsBySoH counts = {0, 0, 0};
  const int ratedCapacity = 120;

  for (int i = 0; i < nBatteries; ++i) {
    double soh = calculateSoH(presentCapacities[i], ratedCapacity);

    if (soh > 80.0 && soh <= 100.0) {
      counts.healthy++;
    } else if (soh >= 62.0 && soh <= 80.0) {
      counts.exchange++;
    } else {
      counts.failed++;
    }
  }

  return counts;
}

void testBucketingByHealth() {
  const int presentCapacities[] = {113, 116, 80, 95, 92, 70};
  const int numberOfBatteries = sizeof(presentCapacities) / sizeof(presentCapacities[0]);
  printf("Counting batteries by SoH...\n");
  struct CountsBySoH counts = countBatteriesByHealth(presentCapacities, numberOfBatteries);
  assert(counts.healthy == 2);
  assert(counts.exchange == 3);
  assert(counts.failed == 1);
  printf("Done counting :)\n");
}

int main() {
  testBucketingByHealth();
  return 0;
}
