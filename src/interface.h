class IInterface {
   public:
    virtual void Init(int width, int height) = 0;
    virtual void Start()    = 0;
    virtual void Update(char **ppData, int *psize) = 0;
    virtual void Shutdown() = 0;
};