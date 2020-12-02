#include<cstdio>


class Mere {
public:
  virtual void message(){
    printf("je suis la classe Mere\n");
  }
  virtual ~Mere() {}
};


class Fille : public Mere {
public:
  void message(){
    printf("je suis la classe Fille\n");
  }
};


int main(){
  Fille *fille= new Fille;

  fille->message();

  Mere *mere=fille;
  mere->message();

  printf("Mere: %lu\n",sizeof(Mere));
  printf("Fille: %lu\n",sizeof(Fille));


  delete mere;
}

/*
int main(){
Mere *mere=NULL;

mere->message();
}
*/

/*
int main() {
  Fille *f = new Fille();
  Mere &m = *f;
  m.message();
  delete f;
}
*/