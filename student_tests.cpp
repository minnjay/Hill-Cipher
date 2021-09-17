#include "catch.hpp"
#include "Hill.hpp"
#include "Matrix.hpp"

TEST_CASE( "default constructor", "[Hill]" )
{
  INFO("Hint: default constructor (linear getE/D() must work)");
  Hill LS;
  Matrix E(std::vector<int>{2,4,3,5}, 2, 2); // det is -2
  Matrix D(std::vector<int>{12,2,16,28}, 2, 2); // det is 304

  REQUIRE(LS.getE().equal(E));
  REQUIRE(LS.getD().equal(D));

  Matrix test(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3); //det is 0
  Matrix testerror(std::vector<int>{12, 2, 16, 28, 34, 45, 56, 23, 2}, 2, 3);


  Matrix testE(std::vector<int>{1, 3, 3, 5, 5, 6, 3, 2, 3}, 3, 3); // det is -3
  Matrix fourE(std::vector<int>{1, 3, 3, 5, 5, 6, 3, 2, 3, 4, 6, 2, 3, 5, 8, 6}, 4, 4); // det is -49

  Hill arjun;
  REQUIRE(arjun.setE(testE));
  REQUIRE(arjun.getE().equal(testE));

  REQUIRE(LS.calculateDeterminant(testE) == -3);
  REQUIRE(LS.calculateDeterminant(E) == -2);
  REQUIRE(LS.calculateDeterminant(test) == 0);
  REQUIRE(LS.calculateDeterminant(D) == 304);
  //REQUIRE(LS.calculateDeterminant(fourE) == -49);


  /*Matrix x = arjun.inv_mod(E);

  REQUIRE(x.get(0, 0) == 12);
  REQUIRE(x.get(0, 1) == 16);
  REQUIRE(x.get(1, 0) == 2);
  REQUIRE(x.get(1, 1) == 28);*/

}
