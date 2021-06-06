//Arrays en C++
#include <tr1/array> //en C++11 se incluye <array>
const int TAM_ARRAY = 3;
std::tr1::array <int, TAM_ARRAY> mi_array = {1,2,3};
mi_array[0] = 0;
typedef std::tr1::array<int , TAM_ARRAY> TipoArray;
TipoArray otro_array[];
otro_array.size();
