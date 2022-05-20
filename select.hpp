#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Not: public Select{
	private:
		Select* input;
	public:
		Select_Not(Select* selection){
			input = selection;
		}

		~Select_Not(){
			delete input;
		}

		bool select(const Spreadsheet* sheet, int row) const{
			if(input -> select(sheet, row)){
				return false;
			}
			else{
        			return true;
			}
		}
};
	

class Select_Or: public Select{
	private:
   		Select* input1;
   		Select* input2;
	public:
   		Select_Or(Select* in1, Select* in2){
			input1 = in1;
			input2 = in2;
		}
  		~Select_Or(){
			delete input1;
			delete input2;
		}

		bool select(const Spreadsheet* sheet, int row) const{
			if((input1->select(sheet,row))||(input2->select(sheet,row))){
				return true;
			}
			else{
				return false;
			}
		}
};  

class Select_Contains : public Select{

	private:
		int col_num;
		String name;

	public:
		Select_Contains(const Spreadsheet* sheet, const String& column, const string& name){

			col_num = sheet->get_column_by_name(column);
			this->name = name;		

		}

		bool select(const Spreadsheet* sheet, int row) const{
		
			if(col_num != -1){
				if((sheet->cell_data(row, col_num)).find(name) != std::string::npos){
					return true;
				}
			}

			return false;

		}

};

class Select_And : public Select{

	private:
		Select* input1;
		Select* input2;

	public:
		Select_And(Select* in1, Select* in2){
			input1 = in1;
			input2 = in2;
		}

		~Select_And(){
			delete input1;
			delete input2;
		}

		bool select(const Spreadsheet* sheet, int row) const {
			if(input1->select(sheet, row) && input2->select(sheet, row)){
				return true;
			}
			return false;
		}

};

#endif //__SELECT_HPP__
