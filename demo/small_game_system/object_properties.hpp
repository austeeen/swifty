
template <class T>
class LoadTime: virtual public T {
public:
    LoadTime(ObjectContainer<T> * parent) {
        parent->doRegister<LoadTime<T>>(this);
    }

    virtual ~LoadTime() {
        parent->unRegister<LoadTime<T>>(this);
    }

    virtual void build() = 0;
    virtual void setUp() = 0;
};

template <class T>
class Updated: virtual public T {
public:
    Updated(ObjectContainer<T> * parent) {
        parent->doRegister<Updated<T>>(this);
    }

    virtual ~Updated() {
        parent->unRegister<Updated<T>>(this);
    }

    virtual void update() = 0;
    virtual void lateUpdate() = 0;
};

template <class T>
class Rendered: virtual public T {
public:
    Rendered(ObjectContainer<T> * parent) {
        parent->doRegister<Rendered<T>>(this);
    }

    virtual ~Rendered() {
        parent->unRegister<Rendered<T>>(this);
    }

    virtual void render() = 0;
};
