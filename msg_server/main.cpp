#include "SerClientManager.h"

int main()
{
  SerClientManager* p = new SerClientManager("192.168.155.128", 8000);
  p->start();
}
