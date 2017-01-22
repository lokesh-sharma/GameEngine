#ifndef COLLIDER_H
#define COLLIDER_H


class Collider
{
public:
    enum
    {
        TYPE_BOUNDINGSPHERE,
        TYPE_AABB,
        TYPE_SIZE
    };
    Collider(int type ): m_type(type){};
    inline int getType() const { return m_type;}
private:
    int m_type;
};

#endif // COLLIDER_H
