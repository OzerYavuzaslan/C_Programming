#include <stdio.h>
#include <stdlib.h>

void tower_of_hanoi(int disk_num, int source, int aux, int destination)
{
    if(disk_num == 1)
    { //Just pick and place
        printf("Move the disk from tower no: %d to tower no: %d\n", source, destination);
        return;
    }
    //Move all n-1 disk to aux
    tower_of_hanoi(disk_num - 1, source, destination, aux);
    //Move the single disk from source to destination
    tower_of_hanoi(1, source, aux, destination);
    //Move all the n-1 disk kept in auxiliary to destination.
    tower_of_hanoi(disk_num - 1, aux, source, destination);
}

int main()
{
    tower_of_hanoi(3, 1, 3, 2); //En soldaki 3 disk sayýsý, diðerleri de disklerin yerleþtirme sýrasý ayný zamanda deðerler disklerin büyüklüðü olarak da ifade edilmiþtir.
    return 0;
}
