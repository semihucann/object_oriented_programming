#include <iostream>
/*
Ahmet Semih U�an
150160014
*/
#define MAX_OPERATOR_SIZE 100

using namespace std;

class Operator {
    int center_x;
    int center_y;
    int op_size;

public:
    Operator(int x, int y, int size)
    {
        center_x = x;
        center_y = y;
        op_size = size;
    };
    void reset(int new_x, int new_y, int new_size)
    {
        center_x = new_x;
        center_y = new_y;
        op_size = new_size;
    };

    void set_x(int new_x)
    {
        center_x = new_x;
    };
    int get_x()
    {
        return center_x;
    };

    void set_y(int new_y)
    {
        center_y = new_y;
    };
    int get_y()
    {
        return center_y;
    };

    void set_size(int new_size)
    {
        op_size = new_size;
    };
    int get_size()
    {
        return op_size;
    };
};
class ArithmeticOperator : public Operator {
    char sign;
    int* points[2]; //Operat�r�n t�m noktalar�n� 2 boyutlu matriste tuttum
    int length;
    int border_error;
    int conflict_error;

public:
    ArithmeticOperator(int x, int y, int size, char sign);

    char get_sign()
    {
        return sign;
    };
    void print_operator();
    int** get_points()
    {
        return points;
    }; //Operat�r�n t�m noktalar�n� de�i�tirmek i�in (ta��ma i�leminden sonra)
    void set_points(int index, int new_x, int new_y)
    {
        points[0][index] = new_x;
        points[1][index] = new_y;
    };
    int get_length()
    {
        return length;
    }; //Ka� adet nokta bulunuyor
    int get_border()
    {
        return border_error;
    }; //Border hatas� varsa 1 yoksa 0 d�ner
    int get_conflict()
    {
        return conflict_error;
    }; //Border hatas� varsa 1 yoksa 0 d�ner

    void set_border(int error)
    {
        border_error = error;
    };
    void set_conflict(int error)
    {
        conflict_error = error;
    };
};
class OperatorGrid {
    int grid_rows;
    int grid_cols;
    char** grid;
    int num_operators;
    ArithmeticOperator* operators[MAX_OPERATOR_SIZE];

public:
    OperatorGrid(int rows, int cols);
    ~OperatorGrid();
    bool place_operator(ArithmeticOperator*);
    bool move_operator(int x, int y, char direction, int move_by);
    void print_operators();
    int find_operator(int x, int y); //Verilen noktan�n hangi operat�re ait oldu�unun indexini d�nd�r�r
    bool own(int x, int y, int index); //Verilen nokta kendi noktas� m� de�il mi onu d�nd�r�r (ta��mada kullanmak i�in)
};

OperatorGrid::OperatorGrid(int rows, int cols)
{ //Constructor//
    num_operators = 0; //Default olarak 0 atad�m
    grid_rows = rows;
    grid_cols = cols;
    grid = new char* [rows];

    for (int i = 0; i < rows; i++) {
        grid[i] = new char[cols];
    }

    for (int a = 0; a < rows; a++) {
        for (int b = 0; b < cols; b++) {
            grid[a][b] = '0'; //Dinamik olarak grid olu�turup default olarak 0 ile doldurdum
        }
    }
}

OperatorGrid::~OperatorGrid()
{
    cout << "DESTRUCTOR: GIVE BACK[" << grid_rows << "," << grid_cols << "] chars." << endl;
    cout << "DESTRUCTOR: GIVE BACK[" << num_operators << "] Operators." << endl;
    for (int i = 0; i < grid_rows; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

bool OperatorGrid::place_operator(ArithmeticOperator* newElement)
{
    bool result = true;

    //Error Control
    for (int i = 0; i < newElement->get_length(); i++) {
        if (newElement->get_points()[0][i] < 1 || newElement->get_points()[1][i] < 1 || newElement->get_points()[0][i] > grid_rows || newElement->get_points()[1][i] > grid_cols) {
            newElement->set_border(1); //Border hatas� var border erroru 1 yap
        } else if (grid[newElement->get_points()[0][i] - 1][newElement->get_points()[1][i] - 1] != '0') {
            newElement->set_conflict(1); //Conflict hatas� var conflict erroru 1 yap
        }
    }

    char tmp_sign = newElement->get_sign();
    int tmp_size = newElement->get_size();
    int tmp_x = newElement->get_x();
    int tmp_y = newElement->get_y();

    //Place i�lemini kontrol et
    if (newElement->get_border() == 0 && newElement->get_conflict() == 0) {
        result = true; //Error yok yerle�tirme i�lemini yap
        operators[num_operators] = newElement;
        num_operators++;

        for (int i = 0; i < newElement->get_length(); i++) {
            grid[newElement->get_points()[0][i] - 1][newElement->get_points()[1][i] - 1] = newElement->get_sign();
        }
        cout << "SUCCESS: Operator " << tmp_sign << " with size " << tmp_size << " is placed on (" << tmp_x << "," << tmp_y << ")." << endl;
    } else if (newElement->get_border() != 0 && newElement->get_conflict() == 0) {
        cout << "BORDER ERROR: Operator " << tmp_sign << " with size " << tmp_size << " can not be placed on (" << tmp_x << "," << tmp_y << ")." << endl;
        result = false; //Border error var
    } else if (newElement->get_conflict() != 0 && newElement->get_border() == 0) {
        cout << "CONFLICT ERROR: Operator " << tmp_sign << " with size " << tmp_size << " can not be placed on (" << tmp_x << "," << tmp_y << ")." << endl;
        result = false; //Conclict error var
    } else if (newElement->get_conflict() != 0 && newElement->get_border() != 0) {
        cout << "BORDER ERROR: Operator " << tmp_sign << " with size " << tmp_size << " can not be placed on (" << tmp_x << "," << tmp_y << ")." << endl;
        cout << "CONFLICT ERROR: Operator " << tmp_sign << " with size " << tmp_size << " can not be placed on (" << tmp_x << "," << tmp_y << ")." << endl;
        result = false; //�ki error da var
    }

    return result;
}

bool OperatorGrid::move_operator(int x, int y, char direction, int move_by)
{
    bool result = false;
    int move_border_error = 0;
    int move_conflict_error = 0;

    int index = find_operator(x, y); //Hangi indexteki operator oldu�unu bulduk

    if (index == -1) {
        //Olmayan bir noktay� ta��ma i�lemi yapma, o i�lemi yoksay (�dev pdf inde a��klama yok)
        return false;
    }

    int tmp_x, tmp_y;
    char sign = operators[index]->get_sign();

    for (int i = 0; i < operators[index]->get_length(); i++) {
        tmp_x = operators[index]->get_points()[0][i] - 1; //�ndex e�itleme yapt�k
        tmp_y = operators[index]->get_points()[1][i] - 1;

        if (direction == 'U') {
            if (tmp_x - move_by < 0 || tmp_x - move_by > grid_rows - 1) {
                move_border_error = 1; //Border Error
            } else if (grid[tmp_x - move_by][tmp_y] != '0' && own(tmp_x - move_by, tmp_y, index)) {
                move_conflict_error = 1; //Conflict Error
            }
        } else if (direction == 'D') {
            if (tmp_x + move_by < 0 || tmp_x + move_by > grid_rows - 1) {
                move_border_error = 1; //Border Error
            } else if (grid[tmp_x + move_by][tmp_y] != '0' && own(tmp_x + move_by, tmp_y, index)) {
                move_conflict_error = 1; //Conflict Error
            }
        } else if (direction == 'R') {
            if (tmp_y + move_by < 0 || tmp_y + move_by > grid_cols - 1) {
                move_border_error = 1; //Border Error
            } else if (grid[tmp_x][tmp_y + move_by] != '0' && own(tmp_x, tmp_y + move_by, index)) {
                move_conflict_error = 1; //Conflict Error
            }
        } else if (direction == 'L') {
            if (tmp_y - move_by < 0 || tmp_y - move_by > grid_cols - 1) {
                move_border_error = 1; //Border Error
            } else if (grid[tmp_x][tmp_y - move_by] != '0' && own(tmp_x, tmp_y - move_by, index)) {
                move_conflict_error = 1; //Conflict Error
            }
        }
    }

    int last_cent_x = operators[index]->get_points()[0][0]; //Ekran ��kt�s� i�in eski ve yeni koordinatlar� belirliyoruz
    int last_cent_y = operators[index]->get_points()[1][0]; //Ekran ��kt�s� i�in eski ve yeni koordinatlar� belirliyoruz

    int new_cent_x, new_cent_y;
    if (direction == 'U') {
        new_cent_x = last_cent_x - move_by;
        new_cent_y = last_cent_y;
    } else if (direction == 'D') {
        new_cent_x = last_cent_x + move_by;
        new_cent_y = last_cent_y;
    } else if (direction == 'R') {
        new_cent_x = last_cent_x;
        new_cent_y = last_cent_y + move_by;
    } else if (direction == 'L') {
        new_cent_x = last_cent_x;
        new_cent_y = last_cent_y - move_by;
    }
    //Moving Ekrana ��kt�
    if (move_border_error == 0 && move_conflict_error == 0) {
        //Ta��ma i�lemini yap
        char sign = operators[index]->get_sign();
        for (int i = 0; i < operators[index]->get_length(); i++) {
            //Eskiyi operat�r�n koordinatlar�n� temizle
            tmp_x = operators[index]->get_points()[0][i] - 1; //�ndex e�itleme yapt�k
            tmp_y = operators[index]->get_points()[1][i] - 1;
            grid[tmp_x][tmp_y] = '0';
        }
        for (int i = 0; i < operators[index]->get_length(); i++) {
            tmp_x = operators[index]->get_points()[0][i] - 1; //�ndex e�itleme yapt�k
            tmp_y = operators[index]->get_points()[1][i] - 1;

            //Yeni operat�r� doldur
            if (direction == 'U') {
                tmp_x = tmp_x - move_by;
            } else if (direction == 'D') {
                tmp_x = tmp_x + move_by;
            } else if (direction == 'R') {
                tmp_y = tmp_y + move_by;
            } else if (direction == 'L') {
                tmp_y = tmp_y - move_by;
            }
            grid[tmp_x][tmp_y] = sign;
            operators[index]->set_points(i, tmp_x + 1, tmp_y + 1);
        }
        cout << "SUCCESS: " << sign << " moved from (" << last_cent_x << "," << last_cent_y << ") to (" << new_cent_x << "," << new_cent_y << ")." << endl;
        operators[index]->set_x(new_cent_x);
        operators[index]->set_y(new_cent_y);
        result = true;
    } else if (move_border_error == 0 && move_conflict_error == 1) {
        cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << last_cent_x << "," << last_cent_y << ") to (" << new_cent_x << "," << new_cent_y << ")." << endl;
    } else if (move_border_error == 1 && move_conflict_error == 0) {
        cout << "BORDER ERROR: " << sign << " can not be moved from (" << last_cent_x << "," << last_cent_y << ") to (" << new_cent_x << "," << new_cent_y << ")." << endl;
    } else if (move_border_error == 1 && move_conflict_error == 1) {
        cout << "BORDER ERROR: " << sign << " can not be moved from (" << last_cent_x << "," << last_cent_y << ") to (" << new_cent_x << "," << new_cent_y << ")." << endl;
        cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << last_cent_x << "," << last_cent_y << ") to (" << new_cent_x << "," << new_cent_y << ")." << endl;
    }

    return result;
}

int OperatorGrid::find_operator(int x, int y)
{ //Verilen x ve y 'nin hangi indexli operat�r�n eleman� oldu�unu tesbit etme fonksiyonu
    int index = -1; //E�er verilen nokta gridde yoksa -1 d�nd�r�r
    for (int i = 0; i < num_operators; i++) {
        for (int j = 0; j < operators[i]->get_length(); j++) {
            if (x == operators[i]->get_points()[0][j] && y == operators[i]->get_points()[1][j]) {
                index = i;
                break;
            }
        }
    }
    return index; //Operat�r�n indexini d�nd�r�r
}

bool OperatorGrid::own(int x, int y, int index)
{ //Verilen nokta indexteki operat�r�n�n eleman� m� de�ilmi belirler
    bool own = true;

    for (int i = 0; i < operators[index]->get_length(); i++) {
        if (x == operators[index]->get_points()[0][i] - 1 && y == operators[index]->get_points()[1][i] - 1) {
            own = false;
        }
    }
    return own;
}

void OperatorGrid::print_operators()
{
    for (int i = 0; i < num_operators; i++) {
        operators[i]->print_operator();
    }
}

//Derived fonksiyonun constructor� �a��r�l�nca �nce base func constructor� tetiklenir ve o �a��r�l�r bu sebeple x ve y atanmad�
ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign)
    : Operator(x, y, size)
{
    if (sign == '+' || sign == '-' || sign == 'x' || sign == '/') {
        this->sign = sign;
        border_error = 0; //Default atamalar� yap�yoruz
        conflict_error = 0; //Default atamalar� yap�yoruz
        if (sign == '+') {
            length = size * 4 + 1;
        } else if (sign == '-') {
            length = size * 2 + 1;
        } else if (sign == 'x') {
            length = size * 4 + 1;
        } else if (sign == '/') {
            length = size * 2 + 1;
        }
        points[0] = new int[length];
        points[1] = new int[length];

        points[0][0] = x; //Center x of operator			//Koordinatlar� dolduruyoruz
        points[1][0] = y; //Center y of operator			//Koordinatlar� dolduruyoruz

        if (sign == '+') {
            int r;
            for (r = 1; r <= size; r++) {
                points[0][r] = x + r;
                points[1][r] = y;
            }
            int l;
            for (l = 1; l <= size; l++) {
                points[0][r + l - 1] = x - l;
                points[1][r + l - 1] = y;
            }
            int u;
            for (u = 1; u <= size; u++) {
                points[0][r + l + u - 2] = x;
                points[1][r + l + u - 2] = y + u;
            }
            int d;
            for (d = 1; d <= size; d++) {
                points[0][r + l + u + d - 3] = x;
                points[1][r + l + u + d - 3] = y - d;
            }
        } else if (sign == '-') {
            int r;
            for (r = 1; r <= size; r++) {
                points[0][r] = x;
                points[1][r] = y + r;
            }
            int l;
            for (l = 1; l <= size; l++) {
                points[0][r + l - 1] = x;
                points[1][r + l - 1] = y - l;
            }
        } else if (sign == '/') {
            int r;
            for (r = 1; r <= size; r++) {
                points[0][r] = x - r;
                points[1][r] = y + r;
            }
            int l;
            for (l = 1; l <= size; l++) {
                points[0][r + l - 1] = x + l;
                points[1][r + l - 1] = y - l;
            }
        } else if (sign == 'x') {
            int r;
            for (r = 1; r <= size; r++) {
                points[0][r] = x + r;
                points[1][r] = y + r;
            }
            int l;
            for (l = 1; l <= size; l++) {
                points[0][r + l - 1] = x - l;
                points[1][r + l - 1] = y - l;
            }
            int u;
            for (u = 1; u <= size; u++) {
                points[0][r + l + u - 2] = x + u;
                points[1][r + l + u - 2] = y - u;
            }
            int d;
            for (d = 1; d <= size; d++) {
                points[0][r + l + u + d - 3] = x - d;
                points[1][r + l + u + d - 3] = y + d;
            }
        }
    } else {
        cout << "SIGN parameter is invalid!" << endl; //E�er ge�ersiz bir parametre verilirse ekrana ��kt� verir
        this->sign = sign;
    }
}

void ArithmeticOperator::print_operator()
{
    cout << "ARITHMETIC_OPERATOR[" << get_sign() << "], CENTER_LOCATION[" << get_x() << "," << get_y() << "], SIZE[" << get_size() << "]" << endl;
}
/*
		////�al��an �rnek main fonksiyonu ///
int main()
{
    OperatorGrid a(10, 7);
    ArithmeticOperator* x = new ArithmeticOperator(2, 2, 1, 'x');
    ArithmeticOperator* y = new ArithmeticOperator(2, 4, 1, '+');
    ArithmeticOperator* z = new ArithmeticOperator(2, 6, 1, 'x');
    ArithmeticOperator* t = new ArithmeticOperator(2, 1, 9, '/');
    ArithmeticOperator* w = new ArithmeticOperator(9, 4, 3, '-');
    ArithmeticOperator* xx = new ArithmeticOperator(5, 4, 3, '/');
    ArithmeticOperator* yy = new ArithmeticOperator(5, 4, 3, '-');
    ArithmeticOperator* zz = new ArithmeticOperator(5, 2, 1, '-');
    ArithmeticOperator* tt = new ArithmeticOperator(7, 6, 1, '/');
    ArithmeticOperator* ww = new ArithmeticOperator(5, 6, 1, '+');
    a.place_operator(x);
    a.place_operator(y);
    a.place_operator(z);
    a.place_operator(t);
    a.place_operator(w);
    a.place_operator(xx);
    a.place_operator(yy);
    a.place_operator(zz);
    a.place_operator(tt);
    a.place_operator(ww);
    a.move_operator(1, 1, 'D', 2);
    a.move_operator(5, 1, 'D', 5);
    a.move_operator(1, 1, 'D', 2);
    a.move_operator(2, 4, 'L', 1);
    a.move_operator(2, 4, 'L', 2);
    a.move_operator(8, 5, 'L', 3);
    a.move_operator(1, 7, 'D', 5);
    a.move_operator(10, 1, 'R', 7);
    a.move_operator(5, 4, 'U', 3);
    a.print_operators();
    return 0;
}
*/
