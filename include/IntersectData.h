#ifndef INTERSECTDATA_H_INCLUDED
#define INTERSECTDATA_H_INCLUDED

class IntersectData
{
public:
    IntersectData(const bool doesintersect , const float distance):
    m_doesIntersect(doesintersect) , m_distance(distance){}
    inline bool getDoesIntersect() const { return m_doesIntersect ;}
    inline float getDistance() const { return m_distance ;}
private:
    const bool m_doesIntersect;
    const float m_distance;
};


#endif // INTERSECTDATA_H_INCLUDED
