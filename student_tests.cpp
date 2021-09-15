#include "catch.hpp"
#include "Hill.hpp"
#include "Matrix.hpp"

TEST_CASE( "default constructor", "[Hill]" )
{
  INFO("Hint: default constructor (linear getE/D() must work)");
  Hill LS;
  Matrix E(std::vector<int>{2,4,3,5}, 2, 2);
  Matrix D(std::vector<int>{12,2,16,28}, 2, 2);

  REQUIRE(LS.getE().equal(E));
  REQUIRE(LS.getD().equal(D));

  Matrix test(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
  Matrix testerror(std::vector<int>{12, 2, 16, 28, 34, 45, 56, 23, 2}, 2, 3);


  Matrix testE(std::vector<int>{1, 3, 3, 5, 5, 6, 3, 2, 3}, 3, 3);
  //Matrix testD(std::vector<int>{12, 2, 16, 28}, 2, 2);
  Hill arjun;
  REQUIRE(arjun.setE(testE));
  REQUIRE(arjun.getE().equal(testE));

  /*Matrix x = arjun.inv_mod(E);

  REQUIRE(x.get(0, 0) == 12);
  REQUIRE(x.get(0, 1) == 16);
  REQUIRE(x.get(1, 0) == 2);
  REQUIRE(x.get(1, 1) == 28);*/

}
