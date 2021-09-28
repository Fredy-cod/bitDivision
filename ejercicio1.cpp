#include <iostream>
#include <bitset>
#define bitSize 8 //Dimension de bits a operar.
#define bitZero bitset<bitSize>(0) //Constante global de 0 como formato bitset.

using namespace std;
//Variable global de la unidad como formato bitset.
bitset<bitSize> unity(1);
//Suma de binarios, devuelve la suma de add1 y add2.
bitset<bitSize> bitAdd(bitset<bitSize> &add1, bitset<bitSize> &add2){
  bool carry = 0;
  bitset<bitSize> result=bitZero;
  for (int i=0; i<bitSize; i++){
    if (carry==0){
      if (add1[i]==add2[i]){
        if (add1[i]==1) carry=1;
        result[i]=0;
      }
      else result[i]=1;
      continue;
    }
    else {
      if (add1[i]==add2[i]){
        if (add1[i]==0) carry=0;
        result[i]=1;
      }
      else result[i]=0;
    }
  }
  return result;
}
//Complemento a 2 del binario number en la variable result.
void compTwo(bitset<bitSize> &number, bitset<bitSize> &result){
  bitset<bitSize> var= number^(~bitZero);
  result.reset();
  result = bitAdd(var, unity);
}
//Resta de binarios con el complemento a 2.
bitset<bitSize> bitSub(bitset<bitSize> &sub1, bitset<bitSize> &sub2){
  bitset<bitSize> compTwo2;
  bitset<bitSize> result;
  compTwo(sub2, compTwo2);
  result= bitAdd(sub1, compTwo2);
  return result;
}
//Mover bits a la izquierda de aux-Div como bloque.
void moveDivAux(bitset<bitSize> &Div, bitset<bitSize> &aux){
  bool var= Div[bitSize-1];
  Div= (Div<<1);
  aux= (aux<<1);
  aux[0]= var;
}
//Division de binarios.
void bitDivision(bitset<bitSize> &Div, bitset<bitSize> &div){
  bitset <bitSize> aux= bitZero;
  for (int i=bitSize; i>0; i--){
    moveDivAux(Div, aux);
    if (aux.to_ulong()<div.to_ulong()){
        Div[0]=0;
    }
    else{
        Div[0]=1;
        aux= bitSub(aux, div);
    }
  }
  cout << "El cociente de la operación es: " << Div.to_ulong() << endl;
  cout << "El residuo de la operación es: " << aux.to_ulong() << endl;
}


int main() {
  int DivInt, divInt;
  do{
    system("clear||cls");
    cout << "Ingrese 2 números menores o iguales a " << (~bitZero).to_ulong() << endl;
    cout << "Ingrese el dividendo: ";
    cin >> DivInt;
    cout << "Ingrese el divisor: ";
    cin >> divInt;
  } while ((DivInt > (~bitZero).to_ulong()) || (divInt > (~bitZero).to_ulong()));
  bitset <bitSize> Div(DivInt);
  bitset <bitSize> div(divInt);

  bitDivision(Div, div);
}
