#include "spreadsheet.hpp"
#include "select.hpp"

#include "gtest/gtest.h"
TEST(ContainsTest, ContainsOneLetter){
Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    string one = "Brian Becker 21 computer science \n";
    string two = "Joe Jackson 21 mathematics \n";
    string printed = one +two;

    stringstream ss;
    sheet.set_selection(new Select_Contains(&sheet, "Last", "c"));
    sheet.print_selection(ss);
    
    EXPECT_EQ(ss.str(), printed);
}
TEST(ContainsTest, ContainsCapital){
Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","DOLE","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","DOLE","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});
 	string one = "Diane DOLE 20 computer engineering \n";
        string two = "Dominick DOLE 22 communications \n";
        string printed = one +two;

        stringstream ss;
        sheet.set_selection(new Select_Contains(&sheet, "Last", "DOLE"));
        sheet.print_selection(ss);

        EXPECT_EQ(ss.str(), printed);
}
TEST(AndTest,BothTrue) {
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    Select_And* x = new Select_And(new Select_Contains(&sheet, "Last", "Summers"), new Select_Contains(&sheet, "Age", "21"));
    sheet.set_selection(x);

    EXPECT_TRUE(x->select(&sheet, 4));
}

TEST(AndTest,BothFalse) {
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    Select_And* x = new Select_And(new Select_Contains(&sheet, "Last", "Golwalla"), new Select_Contains(&sheet, "First", "Mariam"));
    sheet.set_selection(x);

    EXPECT_FALSE(x->select(&sheet, 2));
}
TEST(AndTest,OneTrueOneFalse) {
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    Select_And* x = new Select_And(new Select_Contains(&sheet, "Last", "Jackson"), new Select_Contains(&sheet, "First", "Michael"));
    sheet.set_selection(x);

    EXPECT_FALSE(x->select(&sheet, 3));
}

TEST(AndTest,EmptyString) {
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    Select_And* x = new Select_And(new Select_Contains(&sheet, "Last", ""), new Select_Contains(&sheet, "Age", ""));
    sheet.set_selection(x);

    EXPECT_TRUE(x->select(&sheet, 2));
}
TEST(AndTest,PartialWord) {
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    Select_And* x = new Select_And(new Select_Contains(&sheet, "Last", "Gen"), new Select_Contains(&sheet, "Major", "physics"));
    sheet.set_selection(x);

    EXPECT_TRUE(x->select(&sheet, 8));
}

TEST(OrTest, TestNormalOr){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second","Third"});
    sheet.add_row({"one", "two", "three"});
    sheet.add_row({"four", "five", "six"});
    sheet.add_row({"seven", "eight", "nine"});

    stringstream out;
    sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "First", "e"), new Select_Contains(&sheet, "First", "r")));
    sheet.print_selection(out);

    string expected = "one two three \nfour five six \nseven eight nine \n";

    EXPECT_EQ(out.str(), expected);
}

TEST(OrTest, TestCaptialOr) {
    Spreadsheet sheet;
    sheet.set_column_names({"Front", "Last"});
    sheet.add_row({"Rishab", "Dudhia"});
    sheet.add_row({"Fadi", "Zaki"});

    stringstream out;
    sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Last", "Z"), new Select_Contains(&sheet, "Last", "D")));
    sheet.print_selection(out);

    string expected = "Rishab Dudhia \nFadi Zaki \n";
  
    EXPECT_EQ(out.str(), expected);
}
    
TEST(OrTest, OrWrongColumn){
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","DOLE","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","DOLE","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    stringstream out;
    sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "age", "2"), new Select_Contains(&sheet, "age", "1")));
    sheet.print_selection(out);
    
    string expected = "";

    EXPECT_EQ(out.str(), expected);
}

TEST (OrTest, ORandAND) {
    Spreadsheet sheet;
    sheet.set_column_names({"First", "Last", "Position"});
    sheet.add_row({"Lebron", "James", "Power Forward"});
    sheet.add_row({"Steph", "Curry", "Point Guard"});
    sheet.add_row({"Dame", "Lillard", "Point Guard"});
    sheet.add_row({"Joel", "Embiid", "Center"});
    sheet.add_row({"Anthony", "Davis", "Center"});
    sheet.add_row({"Kobe", "Bryant", "Shooting Guard"});

    stringstream out;
    sheet.set_selection(new Select_Or(
      new Select_And(
	new Select_Contains(&sheet, "Position", "Center"),
	new Select_Contains(&sheet, "Position", "Davis")),
      new Select_Contains(&sheet, "Position", "Guard")));
    sheet.print_selection(out);

    string expected = "Steph Curry Point Guard \nDame Lillard Point Guard \nKobe Bryant Shooting Guard \n";

    EXPECT_EQ(out.str(), expected);
}

TEST (OrTest, OrNotFound) {
    Spreadsheet sheet;
    sheet.set_column_names({"First", "Last", "Position"});
    sheet.add_row({"Lebron", "James", "Power Forward"});
    sheet.add_row({"Steph", "Curry", "Point Guard"});
    sheet.add_row({"Dame", "Lillard", "Point Guard"});
    sheet.add_row({"Joel", "Embiid", "Center"});
    sheet.add_row({"Anthony", "Davis", "Center"});
    sheet.add_row({"Kobe", "Bryant", "Shooting Guard"});

    stringstream out;
    sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Last", "james"), new Select_Contains(&sheet, "Last", "davis")));
    sheet.print_selection(out);

    string expected = "";

    EXPECT_EQ(out.str(), expected);
}

TEST (OrTest, OrAllCaps) {
    Spreadsheet sheet;
    sheet.set_column_names({"FIRST", "SECOND", "THIRD"});
    sheet.add_row({"ONE", "TWO", "THREE"});
    sheet.add_row({"FOUR", "FIVE", "SIX"});
    sheet.add_row({"SEVEN", "EIGHT", "NINE"});

    stringstream out;
    sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "SECOND", "FIVE"), new Select_Contains(&sheet, "THIRD", "FOUR")));
    sheet.print_selection(out);

    string expected = "FOUR FIVE SIX \n";

    EXPECT_EQ(out.str(), expected);
}

TEST (NotTest, NormalNot) {
    Spreadsheet sheet;
    sheet.set_column_names({"First", "Last", "Position"});
    sheet.add_row({"Lebron", "James", "Power Forward"});
    sheet.add_row({"Steph", "Curry", "Point Guard"});
    sheet.add_row({"Dame", "Lillard", "Point Guard"});
    sheet.add_row({"Joel", "Embiid", "Center"});
    sheet.add_row({"Anthony", "Davis", "Center"});
    sheet.add_row({"Kobe", "Bryant", "Shooting Guard"});

    stringstream out;
    sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "First", "e")));
    sheet.print_selection(out);

    string expected = "Anthony Davis Center \n";

    EXPECT_EQ(out.str(), expected);
}

TEST (NotTest, CapitalNot) {
    Spreadsheet sheet;
    sheet.set_column_names({"First", "Last", "Position"});
    sheet.add_row({"Lebron", "James", "Power Forward"});
    sheet.add_row({"Steph", "Curry", "Point Guard"});
    sheet.add_row({"Dame", "Lillard", "Point Guard"});
    sheet.add_row({"Joel", "Embiid", "Center"});
    sheet.add_row({"Anthony", "Davis", "Center"});
    sheet.add_row({"Kobe", "Bryant", "Shooting Guard"});

    stringstream out;
    sheet.set_selection(new Select_Not(
      new Select_Or(
	new Select_Contains(&sheet, "First", "L"),
	new Select_Contains(&sheet, "Last", "L"))));
    sheet.print_selection(out);

    string expected = "Steph Curry Point Guard \nJoel Embiid Center \nAnthony Davis Center \nKobe Bryant Shooting Guard \n";

    EXPECT_EQ(out.str(), expected);
}

TEST (NotTest, NotWrongColumn) {
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second","Third"});
    sheet.add_row({"one", "two", "three"});
    sheet.add_row({"four", "five", "six"});
    sheet.add_row({"seven", "eight", "nine"});

    stringstream out;
    sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "apple", "x")));
    sheet.print_selection(out);

    string expected = "one two three \nfour five six \nseven eight nine \n";;

    EXPECT_EQ(out.str(), expected);
}

TEST (NotTest, NotNoReturn) {
    Spreadsheet sheet;
    sheet.set_column_names({"First","Second","Third"});
    sheet.add_row({"one", "two", "three"});
    sheet.add_row({"foure", "five", "sixe"});
    sheet.add_row({"seven", "eight", "nine"});

    stringstream out;
    sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "First", "e")));
    sheet.print_selection(out);

    string expected = "";

    EXPECT_EQ(out.str(), expected);
}

TEST (NotTest, NotAllCaps) {
    Spreadsheet sheet;
    sheet.set_column_names({"FIRST", "SECOND", "THIRD"});
    sheet.add_row({"ONE", "TWO", "THREE"});
    sheet.add_row({"FOUR", "FIVE", "SIX"});
    sheet.add_row({"SEVEN", "EIGHT", "NINE"});

    stringstream out;
    sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "SECOND", "FIVE")));
    sheet.print_selection(out);

    string expected = "ONE TWO THREE \nSEVEN EIGHT NINE \n";

    EXPECT_EQ(out.str(), expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
