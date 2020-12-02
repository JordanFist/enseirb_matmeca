#include<cstdio>


class Mere {
public:
  void message(){
    printf("je suis la classe Mere\n");
  }
  ~Mere() {}
};


class Fille : public Mere {
public:
  void message(){
    printf("je suis la classe Fille\n");
  }
};






int main(){/*
  Fille *fille= new Fille;

  fille->message();

  Mere *mere=fille;
  mere->message();

  printf("Mere: %lu\n",sizeof(Mere));
  printf("Fille: %lu\n",sizeof(Fille));*/

  Fille fille;

  fille.message();

  Mere mere=fille;
  mere.message();

  printf("Mere: %lu\n",sizeof(Mere));
  printf("Fille: %lu\n",sizeof(Fille));

}




/*
int main(){
Mere *mere=NULL;

mere->message();
}*/

