class IInterface {
   public:
    virtual void Init(int width, int height) = 0;
    virtual void Update(char **ppData, int *psize,int *result) = 0;
    virtual void Shutdown() = 0;
};