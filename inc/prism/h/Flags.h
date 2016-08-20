/**
* Completely and shamefully lifted from Qt's QFlag/QFlags classes and macros and just renamed without the prepended 'Q'.
* These classes allow enums to be treated as datatypes when passed to methods.
* They are also type-safe so that the receiving method is expecting the enum and not the basic int equivalent.
* So printFlag(Label::AlignLeft) works whilst printFlag(2) doesn't.
* 
* For example,
*
* class Label {
* private:
* 	enum Alignment { AlignLeft = 0x1, AlignRight = 0x2 }
* 	PRISM_DECLARE_FLAGS(AlignFlags, Alignment)
* }

* // outside class def
* PRISM_DECLARE_OPERATORS_FOR_FLAGS(Label::AlignFlags)

* void printFlag(Label::AlignFlags f) {
*     if (f == Label::AlignLeft) std::cout << "AlignLeft" << std::endl;
*     else if (f == Label::AlignRight) std::cout << "AlignRight" << std::endl;
*     else std::cout << f << std::endl;
* }
* 
* int main(int argc, char** argv) {
*     printFlag(Label::AlignLeft);
* }
*/

#ifndef PRISM_FLAGS_H
#define PRISM_FLAGS_H

namespace prism {
class Flag
{
    int i;
public:
    inline Flag(int i);
    inline operator int() const { return i; }
};

inline prism::Flag::Flag(int ai) : i(ai) {}

template<typename Enum>
class Flags
{
    typedef void **Zero;
    int i;
public:
    typedef Enum enum_type;
    inline Flags(const Flags &f) : i(f.i) {}
    inline Flags(Enum f) : i(f) {}
    inline Flags(Zero = 0) : i(0) {}
    inline Flags(Flag f) : i(f) {}

    inline Flags &operator=(const Flags &f) { i = f.i; return *this; }
    inline Flags &operator&=(int mask) { i &= mask; return *this; }
    inline Flags &operator&=(unsigned int mask) { i &= mask; return *this; }
    inline Flags &operator|=(Flags f) { i |= f.i; return *this; }
    inline Flags &operator|=(Enum f) { i |= f; return *this; }
    inline Flags &operator^=(Flags f) { i ^= f.i; return *this; }
    inline Flags &operator^=(Enum f) { i ^= f; return *this; }

    inline operator int() const { return i; }

    inline Flags operator|(Flags f) const { Flags g; g.i = i | f.i; return g; }
    inline Flags operator|(Enum f) const { Flags g; g.i = i | f; return g; }
    inline Flags operator^(Flags f) const { Flags g; g.i = i ^ f.i; return g; }
    inline Flags operator^(Enum f) const { Flags g; g.i = i ^ f; return g; }
    inline Flags operator&(int mask) const { Flags g; g.i = i & mask; return g; }
    inline Flags operator&(unsigned int mask) const { Flags g; g.i = i & mask; return g; }
    inline Flags operator&(Enum f) const { Flags g; g.i = i & f; return g; }
    inline Flags operator~() const { Flags g; g.i = ~i; return g; }

    inline bool operator!() const { return !i; }

    inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f) ); }
};
}

#define PRISM_DECLARE_FLAGS(Flgs, Enum)\
typedef prism::Flags<Enum> Flgs;

#define PRISM_DECLARE_OPERATORS_FOR_FLAGS(Flgs)\
inline prism::Flags<Flgs::enum_type> operator|(Flgs::enum_type f1, Flgs::enum_type f2) \
{ return prism::Flags<Flgs::enum_type>(f1) | f2; } \
inline prism::Flags<Flgs::enum_type> operator|(Flgs::enum_type f1, prism::Flags<Flgs::enum_type> f2) \
{ return f2 | f1; }



#endif // PRISM_FLAGS_H
