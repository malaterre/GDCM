#include <string>
#include <map>
#include <iterator>
#include <iostream>

class treeitemsx;
typedef std::map<std::string, treeitemsx> mtypex;
class treeitemsx {
public:
  mtypex mtree;
  void print(std::ostream &os, std::string const &indent = "") const
    {
    if( !mtree.empty() )
      {
      // std::copy(mtree.begin(), mtree.end(), std::ostream_iterator<std::string, treeitemsx>(os, "\n"));
      std::map<std::string, treeitemsx>::const_iterator it = mtree.begin();
      os << "Size: " << mtree.size() << std::endl;
      for( ; it != mtree.end(); ++it)
        {
        os << indent << it->first << std::endl;
        it->second.print(os, "\t"); 
        }
      }
    }
};

typedef std::pair<std::string, treeitemsx> Map_Pair;

int main()
{
  treeitemsx mbase;
  Map_Pair x, y, z, z1;
  x.first="forlder 1";
  y.first="forlder 2";
  z.first="file 2.1";
  z1.first="file 1.1";
 
  x.second.mtree.insert(y);
  x.second.mtree.insert(z);
  mbase.mtree.insert(x); 
  mbase.mtree.insert(z1); 

  mbase.print(std::cerr);
  return 0;
}

