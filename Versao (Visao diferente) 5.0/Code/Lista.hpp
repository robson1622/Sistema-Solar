
class Astro;
class Lista{
    private:
        Astro *p;
        Lista *next;
    public:
        //Criar Astro
        Lista();
        ~Lista();
        void start(void);

        //Adicionar Astro
        void insert(Astro* elemento);

        //Pegar proximo
        Lista* getProximo(void);

        //Pegar Elemento
        Astro* getAstro(void);

        //Apaga listas e astros
        void destroy(void);
};

