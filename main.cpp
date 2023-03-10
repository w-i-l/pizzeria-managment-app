#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;


// Ingredient
///////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Ingredient{
    private:

        char* nume;
        // glucide, lipide, proteine
        int* macronutrienti;
        bool de_post;
        // 0.ZZ/MM/YY
        float data_expirarii;
        // kg
        float cantitate;

    public:

        // getteri

        const char* get_nume() { return this->nume; }
        const int* get_macronutrienti() { return this->macronutrienti; }
        bool get_de_post() { return this->de_post; }
        float get_data_expirarii() { return this->data_expirarii; }
        float get_cantitate() { return this->cantitate; }

        // setteri

        void set_nume(const char* nume_nou){
            if(this->nume != NULL){
                delete[] this->nume;
            }

            this->nume = new char[strlen(nume_nou)+1];

            strcpy(this->nume, nume_nou);
        }

        void set_macronutrienti(int* macronutrienti_nou){
            if(this->macronutrienti == NULL){
                this->macronutrienti = new int[3];
            }

            for(int i=0; i<3; i++){
                this->macronutrienti[i] = macronutrienti_nou[i];
            }
        }

        void set_de_post(bool de_post_nou){ this->de_post = de_post_nou; }
        void set_data_expirarii(float data_expirarii_nou){ this->data_expirarii = data_expirarii_nou; }
        void set_cantitate(float cantitate_nou){ this->cantitate = cantitate_nou; }

        // contructori
        Ingredient();
        Ingredient(char* nume, int* macronutrienti, bool de_post, float data_expirarii, float cantitate);
        Ingredient(char* nume, int* macronutrienti);
        Ingredient(char* nume, float cantitate);
        Ingredient(const Ingredient &obj);

        // destructor
        ~Ingredient();

        // operatori
        Ingredient& operator=(const Ingredient& obj);
        
        // friend
        friend ostream& operator<<(ostream& out, const Ingredient& obj);
        friend istream& operator>>(istream& in, Ingredient& obj);

        // methods
        bool expirat();
        bool in_stoc();

    
};


Ingredient::Ingredient(){
    
    this->nume = new char[5];
    strcpy(this->nume, "none");

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = 0;
    
    this->de_post = false;
    this->data_expirarii = 0.000000;
    this->cantitate = 0.0;
}


Ingredient::Ingredient(char* nume, int* macronutrienti, bool de_post, float data_expirarii, float cantitate){
    
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = macronutrienti[i];
    
    this->de_post = de_post;
    this->data_expirarii = data_expirarii;
    this->cantitate = cantitate;
}


Ingredient::Ingredient(char* nume, int* macronutrienti){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = macronutrienti[i];

    this->de_post = false;
    this->data_expirarii = 0.000000;
    this->cantitate = 0.0;
}


Ingredient::Ingredient(char* nume, float cantitate){
    
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = 0;

    this->de_post = false;
    this->data_expirarii = 0.000000;
    this->cantitate = cantitate;
}


Ingredient::Ingredient(const Ingredient &obj){

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = obj.macronutrienti[i];
    
    this->de_post = obj.de_post;
    this->data_expirarii = obj.data_expirarii;
    this->cantitate = obj.cantitate;
}


Ingredient::~Ingredient(){
    if(this->macronutrienti != NULL){
        delete[] this->macronutrienti;
        this->macronutrienti = NULL;
    }
    
    if(this->nume != NULL){
        delete[] this->nume;
        this->nume = NULL;
    }
}


Ingredient&  Ingredient::operator=(const Ingredient& obj){
    
    if(this != &obj){
        if(this->macronutrienti != NULL){
            delete[] this->macronutrienti;
            this->macronutrienti = NULL;
        }
        
        if(this->nume != NULL){
            delete[] this->nume;
            this->nume = NULL;
        }

        this->nume = new char[5];
        strcpy(this->nume, obj.nume);

        this->macronutrienti = new int[3];
        for(int i=0; i<3; i++)
            this->macronutrienti[i] = obj.macronutrienti[i];
        
        this->de_post = obj.de_post;
        this->data_expirarii = obj.data_expirarii;
        this->cantitate = obj.cantitate;
    }

    return *this;
}


ostream& operator<<(ostream& out, const Ingredient& obj){

    out << "Detalii ingredient:" << endl;
    out << "Nume: " << obj.nume << endl;
    out << "Macronutrienti: " << obj.macronutrienti[0] << "g glucide " 
        << obj.macronutrienti[1] << "g lipide "
        << obj.macronutrienti[2] << "g proteine" << endl;
    out << "De post: " << (obj.de_post ? "Da" : "Nu") << endl;
    out << "Data expirarii: " << (int)(obj.data_expirarii * 100) << "."
        << (int)(obj.data_expirarii * 10000) % 100 << "."
        << 20 << (int)(obj.data_expirarii * 1000000) % 100 << endl;
    out << "Cantitate: " << obj.cantitate << " kg" << endl;

    return out;
}


istream& operator>>(istream& in, Ingredient& obj){

    if(obj.macronutrienti != NULL){
        delete[] obj.macronutrienti;
        obj.macronutrienti = NULL;
    }
    
    if(obj.nume != NULL){
        delete[] obj.nume;
        obj.nume = NULL;
    }

    char aux[100];
    cout << "Citire detalii ingredient:" << endl;

    cout << "Nume: ";
    in >> aux;
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);
    cout << endl;

    cout << "Macronutrienti: ";
    obj.macronutrienti = new int[3];
    in >> obj.macronutrienti[0];
    // cout << " ";
    in >> obj.macronutrienti[1]; 
    // cout << " ";
    in >> obj.macronutrienti[2];
    cout << endl;

    cout << "De post (0/1): ";
    in >> obj.de_post;
    cout << endl;

    cout << "Data expirarii (0.DDMMYY): ";
    in >> obj.data_expirarii;
    cout << endl;

    cout << "Cantitate (0.aaaaaa): ";
    in >> obj.cantitate;
    cout << endl;

    return in;
}


// returneaza 1 daca a expirat
bool Ingredient::expirat(){
    time_t t = time(0);
    tm* now = localtime(&t);
    // formatam cum am salvat
    float current_date = (float)now->tm_mday /100 + (float)(now->tm_mon + 1)/10000 + (float)((now->tm_year + 1900) % 100) / 1000000;

    return current_date - this->data_expirarii > 0;
}

// returneaza 1 daca este in stoc
bool Ingredient::in_stoc(){
    return this->cantitate > 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 


// Pizza
///////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Pizza{

    private:
        // diametru pizza in cm
        static int dimensiune_pizza;

        char* nume;
        int numar_ingrediente = 0;
        Ingredient* lista_ingrediente;
        float pret;
    
    public:

        // getteri
        static int get_dimensiune_pizza() { return Pizza::dimensiune_pizza; }
        const char* get_nume() { return this->nume; }
        int get_numar_ingrediente() { return this->numar_ingrediente; }
        const Ingredient* get_lista_ingrediente() { return this->lista_ingrediente; }
        float get_pret() {return this->pret; }

        // setteri
        void set_nume(const char* nume_nou){

            if(this->nume != NULL){
                delete[] this->nume;
            }

            this->nume = new char[strlen(nume_nou)+1];

            strcpy(this->nume, nume_nou);
        }

        void set_lista_ingrediente(int numar_ingrediente_nou, const Ingredient* lista_ingrediente_nou){

            this->numar_ingrediente = numar_ingrediente_nou;

            if(this->lista_ingrediente != NULL){
                delete[] this->lista_ingrediente;
            }

            this->lista_ingrediente = new Ingredient[numar_ingrediente_nou];

            for(int i=0; i<numar_ingrediente_nou; i++){
                this->lista_ingrediente[i] = lista_ingrediente_nou[i];
            }
        }

        void set_pret(float pret_nou){
            this->pret = pret;
        }

        // constructori
        Pizza();
        Pizza(char* nume, int numar_ingrediente, Ingredient* lista_ingrediente, float pret);
        Pizza(char* nume, float pret);
        Pizza(char* nume);
        Pizza(const Pizza& obj);

        // destructor
        ~Pizza();

        // operatori
        Pizza& operator=(const Pizza& obj);

        // friend
        friend ostream& operator<<( ostream& out, const Pizza& obj);
        friend istream& operator>>( istream& in, Pizza& obj);

        // methods
        void afisare_valori_nutritionale();
        bool de_post();
};      

int Pizza::dimensiune_pizza = 30;


Pizza::Pizza(){

    this->nume = new char[5];
    strcpy(this->nume, "none");

    this->numar_ingrediente = 0;
    this->lista_ingrediente = NULL;

    this->pret = 0;
}


Pizza::Pizza(char* nume, int numar_ingrediente, Ingredient* lista_ingrediente, float pret){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_ingrediente = numar_ingrediente;
    this->lista_ingrediente = new Ingredient[numar_ingrediente];
    for(int i=0; i<numar_ingrediente; i++)
        this->lista_ingrediente[i] = lista_ingrediente[i];

    this->pret = pret;
}


Pizza::Pizza(char* nume, float pret){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_ingrediente = 0;
    this->lista_ingrediente = NULL;

    this->pret = pret;
}


Pizza::Pizza(char* nume){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_ingrediente = 0;
    this->lista_ingrediente = NULL;

    this->pret = 0; 
}


Pizza::Pizza(const Pizza& obj){
    
    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->numar_ingrediente = obj.numar_ingrediente;
    this->lista_ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++)
        this->lista_ingrediente[i] = obj.lista_ingrediente[i];

    this->pret = obj.pret;
}


Pizza::~Pizza(){

    if(this->nume != NULL){
        delete this->nume;
    }

    if(this->lista_ingrediente != NULL){
        delete[] this->lista_ingrediente;
    }
}


Pizza& Pizza::operator=(const Pizza& obj){

    if(this->nume != NULL){
        delete this->nume;
    }

    if(this->lista_ingrediente != NULL){
        delete[] this->lista_ingrediente;
    }

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->numar_ingrediente = obj.numar_ingrediente;
    this->lista_ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++)
        this->lista_ingrediente[i] = obj.lista_ingrediente[i];

    this->pret = obj.pret;

}


ostream& operator<<(ostream& out, const Pizza& obj){

    out << "Informatii despre pizza: " << endl;
    out << "Nume: " << obj.nume << endl;
    out << "Lista ingrediente: ";
    for(int i=0; i<obj.numar_ingrediente; i++)
        out << obj.lista_ingrediente[i];
    out << endl;
    out << "Pret: " << obj.pret << endl;

    return out;
}


istream& operator>>(istream& in, Pizza& obj){

    if(obj.nume != NULL){
        delete obj.nume;
    }

    if(obj.lista_ingrediente != NULL){
        delete[] obj.lista_ingrediente;
    }

    char aux[100];
    cout << "Citire informatii: " << endl;

    cout << "Nume: ";
    in >> aux;
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);
    cout << endl;

    cout << "Numar ingrediente: ";
    in >> obj.numar_ingrediente;
    obj.lista_ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++)
        in >> obj.lista_ingrediente[i];
    cout << endl;

    cout << "Pret: ";
    in >> obj.pret;
    cout << endl;

    return in;
}


void Pizza::afisare_valori_nutritionale(){

    int macro[3] = {0};
    cout << "Total macronutrienti: " << endl;
    for(int i=0; i<this->numar_ingrediente; i++){
        const int* aux = this->lista_ingrediente[i].get_macronutrienti();
        // trecem prin macronutrieti
        for(int j=0; j<3; j++){
            macro[j] += aux[j];
        }
    }

    cout << macro[0] << "g glucide " 
        << macro[1] << "g lipide "
        << macro[2] << "g proteine" << endl;

}


bool Pizza::de_post(){
    for(int i=0; i<this->numar_ingrediente; i++){
        if(this->lista_ingrediente[i].get_de_post() == 0){
            return false;
        }
    }

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 


// Angajat
///////////////////////////////////////////////////////////////////////////////////////////////////////// 

class Angajat{
    
    private:

        char* nume;
        char sex;
        float salariu;
        char* nume_job;
        int numar_pizze_facute;
        Pizza* pizze_facute;

    public:

        // getteri
        const char* get_nume() { return this->nume; }
        char get_sex() { return this->sex; }
        float get_salariu() { return this->salariu; }
        const char* get_nume_job() { return this->nume_job; }
        int get_numar_pizze_facute() { return this->numar_pizze_facute; }
        const Pizza* get_pizze_facute() { return this->pizze_facute; };

        // setteri
        void set_nume(const char* nume_nou){

            if(this->nume != NULL){
                delete[] this->nume;
            }

            this->nume = new char[strlen(nume_nou)+1];
            strcpy(this->nume, nume);
        }

        void set_sex(char sex_nou) {this->sex = sex_nou;}
        void set_salariu(float salariu_nou) { this->salariu = salariu_nou; }

        void set_nume_job(const char* nume_job_nou){

            if(this->nume_job != NULL){
                delete[] this->nume_job;
            }

            this->nume_job = new char[strlen(nume_job_nou)+1];
            strcpy(this->nume_job, nume_job_nou);
        }

        void adauga_pizza(Pizza pizza_noua){
            // nu avem nicio pizza facuta
            if(this->pizze_facute == NULL){
                this->pizze_facute = new Pizza[1];
                this->pizze_facute[0] = pizza_noua;
                this->numar_pizze_facute = 1;
                return;
            }

            Pizza* aux = new Pizza[this->numar_pizze_facute + 1];
            for(int i=0; i<this->numar_pizze_facute; i++){
                aux[i] = this->pizze_facute[i];
            }
            aux[this->numar_pizze_facute] = pizza_noua;
            this->numar_pizze_facute ++;

            delete[] this->pizze_facute;
            this->pizze_facute = aux;
        }

        void resetare_pizze_facute(){
            if(this->pizze_facute == NULL) return;

            delete[] this->pizze_facute;
            this->pizze_facute = NULL;
            this->pizze_facute = 0;
        }

        // constructori
        Angajat();
        Angajat(char* nume, char sex, float salariu, char* nume_job, int numar_pizze_facute, Pizza* pizze_facute);
        Angajat(char* nume, char sex);
        Angajat(char* nume, float salariu, char* nume_job);
        Angajat(const Angajat& obj);

        // destructor
        ~Angajat();

        // operatori
        Angajat& operator=(const Angajat& obj);

        // friend
        friend ostream& operator<<(ostream& out, const Angajat& obj);
        friend istream& operator>>(istream& in, Angajat& obj);

        // method
        void executa_pizza();

};

Angajat::Angajat(){
    
    this->nume = new char[5];
    strcpy(this->nume, "none");

    this->sex = 'x';
    this->salariu = 0;
    this->nume_job = new char[5];
    strcpy(this->nume_job, "none");
    this->numar_pizze_facute = 0;
    this->pizze_facute = NULL;
}


Angajat::Angajat(char* nume, char sex, float salariu, char* nume_job, int numar_pizze_facute, Pizza* pizze_facute){
   
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->sex = sex;
    this->salariu = salariu;

    this->nume_job = new char[strlen(nume_job)+1];
    strcpy(this->nume_job, nume_job);

    this->numar_pizze_facute = numar_pizze_facute;
    this->pizze_facute = new Pizza[numar_pizze_facute];
    for(int i=0; i<numar_pizze_facute; i++)
        this->pizze_facute[i] = pizze_facute[i];
}


Angajat::Angajat(char* nume, float salariu, char* nume_job){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->sex = 'x';
    this->salariu = salariu;

    this->nume_job = new char[strlen(nume_job)+1];
    strcpy(this->nume_job, nume_job);

    this->numar_pizze_facute = 0;
    this->pizze_facute = NULL;
}


Angajat::Angajat(char* nume, char sex){
    
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->sex = sex;
    this->salariu = 0;
    
    this->nume_job = new char[5];
    strcpy(this->nume_job, "none");

    this->numar_pizze_facute = 0;
    this->pizze_facute = NULL;
}


Angajat::Angajat(const Angajat& obj){

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->sex = obj.sex;
    this->salariu = obj.salariu;

    this->nume_job = new char[strlen(obj.nume_job)+1];
    strcpy(this->nume_job, obj.nume_job);

    this->numar_pizze_facute = obj.numar_pizze_facute;
    this->pizze_facute = new Pizza[obj.numar_pizze_facute];
    for(int i=0; i<obj.numar_pizze_facute; i++)
        this->pizze_facute[i] = obj.pizze_facute[i];
}


Angajat::~Angajat(){

    if(this->nume != NULL){
        delete[] this->nume;
    }

    if(this->nume_job != NULL){
        delete[] this->nume_job;
    }

    if(this->pizze_facute != NULL){
        delete[] this->pizze_facute;
    }
}


Angajat& Angajat::operator=(const Angajat& obj){

    if(this != &obj){

        if(this->nume != NULL){
            delete[] this->nume;
        }

        if(this->nume_job != NULL){
            delete[] this->nume_job;
        }

        if(this->pizze_facute != NULL){
            delete[] this->pizze_facute;
        }

        this->nume = new char[strlen(obj.nume)+1];
        strcpy(this->nume, obj.nume);
        this->sex = obj.sex;
        this->salariu = obj.salariu;

        this->nume_job = new char[strlen(obj.nume_job)+1];
        strcpy(this->nume_job, obj.nume_job);

        this->numar_pizze_facute = obj.numar_pizze_facute;
        this->pizze_facute = new Pizza[obj.numar_pizze_facute];
        
        for(int i=0; i<obj.numar_pizze_facute; i++)
            this->pizze_facute[i] = obj.pizze_facute[i];
    }

    return *this;
}


ostream& operator<<(ostream& out, const Angajat& obj){

    out << "Detalii despre angajat: " << endl;
    out << "Nume: " << obj.nume << endl;
    out << "Sex: " << obj.sex << endl;
    out << "Salariu: " << obj.salariu << endl;
    out << "Job: " << obj.nume_job << endl;
    out << "Pizze facute: ";
    for(int i=0; i<obj.numar_pizze_facute; i++)
        out << obj.pizze_facute[i];
    out << endl;

    return out;
}


istream& operator>>(istream& in, Angajat& obj){
    char aux[100];
    cout << "Introducere angajat: " << endl;
    cout << "Nume: ";
    in >> aux;
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);
    cout << endl;

    cout << "Sex: ";
    in >> obj.sex;
    cout << endl;

    cout << "Salariu: ";
    in >> obj.salariu;
    cout << endl;
    cout << "Job: ";
    in >> aux;
    obj.nume_job = new char[strlen(aux)+1];
    strcpy(obj.nume_job, aux);
    cout << endl;

    cout << "Numar pizze facute: ";
    in >> obj.numar_pizze_facute;
    for(int i=0; i<obj.numar_pizze_facute; i++)
        in >> obj.pizze_facute[i];
    cout << endl;

    return in;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 


// Pizzerie
///////////////////////////////////////////////////////////////////////////////////////////////////////// 

class Pizzerie{

    private:
        
        char* nume;
        int numar_angajati;
        Angajat* angajati;
        int numar_ingrediente;
        Ingredient* ingrediente;
        float profit;

    public:

        // getteri
        const char* get_nume() { return this->nume; }
        const int get_numar_angajati() { return this->numar_angajati; }
        Angajat* get_angajati() { return this->angajati; }
        const int get_numar_ingrediente() { return this->numar_ingrediente; }
        Ingredient* get_ingrediente() { return this->ingrediente; }
        float get_profit() { return this->profit; }

        // setteri
        void set_nume(const char* nume_nou){

            if(this->nume != NULL) delete[] this->nume;

            this->nume = new char[strlen(nume_nou)+1];
            strcpy(this->nume, nume_nou);
        }

        void adaugare_ingredient(const Ingredient& obj){
            // verificare daca exista si creste cantitate
            // daca nu adaugare
        }

        void stergere_ingredient(const Ingredient& obj){
            // daca exista il sterge
            // daca nu exista nu face nimic
        }

        void adaugare_angajat(const Angajat& obj){
            // verificare daca exista
            // daca nu, il adauga
        }

        void stergere_angajat(const Angajat& obj){
            // daca exista il sterge
            // daca nu exista nu face nimic
        }

        // constructori
        Pizzerie();
        Pizzerie(char* nume, int numar_angajati, Angajat* angajati, int numar_ingrediente, Ingredient* ingrediente, float profit);
        Pizzerie(char* nume, int numar_angajati, int numar_ingrediente);
        Pizzerie(char* nume, float profit);
        Pizzerie(const Pizzerie& obj);

        // deconstructor
        ~Pizzerie();

        // operatori
        Pizzerie& operator=(const Pizzerie& obj);

        // friend
        friend ostream& operator<<(ostream& out, const Pizzerie& obj);
        friend istream& operator>>(istream& in, Pizzerie& obj);

        // methods
        void afisare_angajati_cu_jobu(const char* nume_job);
        void concediere_angajat();
        
        
};


Pizzerie::Pizzerie(){

    this->nume = new char[5];
    strcpy(this->nume, "none");
    this->numar_angajati = 0;
    this->angajati = NULL;
    this->numar_ingrediente = 0;
    this->ingrediente = NULL;
    this->profit = 0;
}


Pizzerie::Pizzerie(char* nume, int numar_angajati, Angajat* angajati, int numar_ingrediente, Ingredient* ingrediente, float profit){
    
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_angajati = numar_angajati;
    this->angajati = new Angajat[numar_angajati];
    for(int i=0; i<numar_angajati; i++)
        this->angajati[i] = angajati[i];

    this->ingrediente = new Ingredient[numar_ingrediente];
    this->numar_ingrediente = numar_ingrediente;
    for(int i=0; i<numar_ingrediente; i++)
        this->ingrediente[i] = ingrediente[i];

    this->profit = profit;
}


Pizzerie::Pizzerie(char* nume, int numar_angajati, int numar_ingrediente){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_angajati = numar_angajati;
    this->angajati = NULL;

    this->numar_ingrediente = numar_ingrediente;
    this->ingrediente = NULL;

    this->profit = 0;
}


Pizzerie::Pizzerie(char* nume, float profit){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_angajati = 0;
    this->angajati = NULL;

    this->numar_ingrediente = 0;
    this->ingrediente = NULL;

    this->profit = profit;
}


Pizzerie::Pizzerie(const Pizzerie& obj){

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->numar_angajati = obj.numar_angajati;
    this->angajati = new Angajat[obj.numar_angajati];
    for(int i=0; i<obj.numar_angajati; i++)
        this->angajati[i] = obj.angajati[i];

    this->ingrediente = new Ingredient[obj.numar_ingrediente];
    this->numar_ingrediente = obj.numar_ingrediente;
    for(int i=0; i<obj.numar_ingrediente; i++)
        this->ingrediente[i] = obj.ingrediente[i];

    this->profit = obj.profit;
}


Pizzerie::~Pizzerie(){

    if(this->nume != NULL) delete[] this->nume;

    if(this->angajati != NULL) delete[] this->angajati;

    if(this->ingrediente != NULL) delete[] this->ingrediente;
}


Pizzerie& Pizzerie::operator=(const Pizzerie& obj){

    if(this->nume != NULL) delete[] this->nume;

    if(this->angajati != NULL) delete[] this->angajati;

    if(this->ingrediente != NULL) delete[] this->ingrediente;       

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->numar_angajati = obj.numar_angajati;
    this->angajati = new Angajat[obj.numar_angajati];
    for(int i=0; i<obj.numar_angajati; i++)
        this->angajati[i] = obj.angajati[i];

    this->numar_ingrediente = obj.numar_ingrediente;
    this->ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++)
        this->ingrediente[i] = obj.ingrediente[i];

    this->profit = obj.profit;
}


ostream& operator<<(ostream& out, const Pizzerie& obj){
    
    out << "Informatii despre Pizzerie: " << endl;
    out << "Nume: " << obj.nume << endl;

    out << "Angajati: " << endl;
    for(int i=0; i<obj.numar_angajati; i++){
        out << obj.angajati[i];
    }
    out <<endl;

    out << "Ingrediente: " << endl;
    for(int i=0; i<obj.numar_ingrediente; i++){
        out << obj.ingrediente[i];
    }
    out << endl;

    out << "Profit: " << obj.profit << endl;
}


istream& operator>>(istream& in, Pizzerie& obj){

    char aux[100];

    cout << "Citire Pizzerie: " << endl;
    cout << "Nume: ";
    in >> aux;
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);
    cout << endl;

    cout << "Numar angajati: ";
    in >> obj.numar_angajati;
    obj.angajati = new Angajat[obj.numar_angajati];
    for(int i=0; i<obj.numar_angajati; i++){
        in >> obj.angajati[i];
    }
    cout << endl;

    cout << "Numar ingrediente: ";
    in >> obj.numar_ingrediente;
    obj.ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++){
        in >> obj.ingrediente[i];
    }
    cout << endl;

    cout << "Profit: ";
    in >> obj.profit;
    cout << endl;
}


int main(){

    // Ingredient i;
    // cout << i << endl;

    int x[] = {12, 43, 10};
    char* nume = "Branza";
    Ingredient i2(nume, x, false, 0.111223, 3);
    // cout << i2 << endl;

    // Ingredient i3("Salam", x);
    // cout << i3 << endl;

    // Ingredient i4(i2);
    // cout << i4 << endl;

    // i4 = i;
    // cout << i4 << endl;

    // cin >> i4;
    // cout << i4 << endl;

    // Ingredient i("branza",x,0,0.100223,0.1);
    // cout << i << endl;
    // cout << i.expirat() << endl;
    // cout << i.in_stoc() << endl;

    // cin >> i;
    // cout << i;

    Ingredient i("branza",x,0,0.100223,0.1);
    Ingredient v[] = {i,i};
    // Pizza p;
    // // cout << p << endl;
    Pizza p1("margherita",2,v,3.13);
    // // cout << p1 << endl;
    // // Pizza p2("pro",10);
    // // cout << p2 << endl;
    // // Pizza p3("saqlami");
    // // cout << p3 << endl;

    Pizza vec[] = {p1,p1};
    // // Pizza p4;
    // // cin >> p4;
    // // cout << p4;

    // p1.afisare_valori_nutritionale();
    // cout << p1.de_post();
    
    Angajat a;
    // cout << a << endl;
    
    Angajat a1("mishu", 'M', 1000.3, "spalator", 2, vec);


    Pizzerie p;
    cout << p << endl;

    Angajat an[] = {a1};

    Pizzerie p2("marco", 1, an , 1, v , 100.0);
    cout <<p2;

    Pizzerie p3;
    p3 = p2;
    cout << p3 << endl;

    return 0;
}