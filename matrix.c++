#include <iostream>
#include <vector>
#include <assert.h>
using std::cin;
using std::cout;
using std::endl;

/*
实现一个向量类，一个矩阵类。在这两个类中，分别重载 “+， -， *(数乘，矩阵乘) ” 基本运算以及 “==，!=，-(负号)， =(赋值)" 操作符，以实现向量、矩阵的基本运算。

要求：
1. 除了重载相应的操作符，也需要实现一个类的一些基本的方法(接口），比如构造、析构、拷贝构造等。

2. 可以使用C++标准模板库(STL)里面的vector类，也可以使用你前一次作业实现的动态数组作为你这次所要实现的向量类的基础。
*/
#if 1
class Vector
{
public:
	typedef std::vector<double> Data;
	static Vector INVALID_VECTOR;

public:
	Vector() {}
	Vector(int length, const double data[])
	{
		_length = length;
		for (int i = 0; i<length; ++i) {
			_data.push_back(data[i]);
		}
	}
	Vector(int length, const double data)
	{
		_length = length;
		for (int i = 0; i<length; ++i) {
			_data.push_back(data);
		}
	}

#if 1
	~Vector() {
		_length = 0;
		Data().swap(_data);
	}
#endif

	int size() const
	{
		return _length;
	}



private:
	Data _data; //_data 使用vector 构建 
	int _length;  //向量的长度
	friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

public:
	//==
	bool operator==(const Vector &rhs) {//判断语句
		if (_length != rhs._length) {
			return false;
		}
		else
		{
			for (int i = 0; i<_length; i++) {
				if (_data[i] != rhs._data[i]) {
					return false;
				}
			}
			return true;
		}
	}

	//!=
	bool operator!=(const Vector &rhs) {

		return(!(*this == rhs));
	}

	// =
	Vector operator=(const Vector &rhs) {//赋值语句 

										 //防止自赋值；
#if 1
		if (_length != rhs._length) {
			return INVALID_VECTOR;
		}
#endif

		if (&rhs == this) {
			return *this;
		}

		for (int i = 0; i<_length; ++i) {
			_data[i] = rhs._data[i];
		}
		return *this;
	}

	// =
	Vector operator=(const double rhs) {//赋值语句 
		for (int i = 0; i<_length; ++i) {
			_data[i] = rhs;
		}
		return *this;
	}

	//+
	Vector operator+(const Vector &rhs)
	{//向量加法
		if (_length == rhs._length) {

			Vector temp;
			temp._length = _length;
			for (int i = 0; i<_length; ++i) {
				temp._data.push_back(_data[i] + rhs._data[i]);
			}
			return temp;
		}

#if 1
		else {
			return INVALID_VECTOR;
		}
#endif
	}

	Vector operator+(const double rhs) {//向量加法

		Vector temp;
		temp._length = _length;
		for (int i = 0; i<_length; ++i) {
			temp._data.push_back(_data[i] + rhs);
		}

		return temp;

	}

	//-
	Vector operator-(const Vector &rhs)
	{ //向量减法
		if (_length == rhs._length) {

			Vector temp;
			temp._length = _length;
			for (int i = 0; i<_length; ++i) {
				temp._data.push_back(_data[i] - rhs._data[i]);
			}
			return temp;
		}

#if 1
		else {
			return INVALID_VECTOR;
		}
#endif
	}

	//-
	Vector operator-(const double rhs)
	{ //向量减法

		Vector temp;
		temp._length = _length;
		for (int i = 0; i<_length; ++i) {
			temp._data.push_back(_data[i] - rhs);
		}
		return temp;
	}

	//*
	Vector operator*(const double num)
	{ //向量对应数乘

		Vector temp;
		temp._length = _length;
		for (int i = 0; i<_length; ++i) {
			temp._data.push_back(_data[i] * num);
		}
		return temp;
	}

	double operator*(const Vector &rhs)
	{ //向量对应数乘
		double temp = 0;
		if (_length != rhs._length) {
			return -1;
		}
		else {
			for (int i = 0; i<_length; i++) {
				temp = temp + _data[i] * rhs._data[i];
			}
			return temp;
		}
	}

	//-
	Vector operator-() {
		Vector temp;
		temp._length = _length;
		for (int i = 0; i<_length; i++) {
			temp._data.push_back(-_data[i]);
		}
		return temp;
	}
	//[]
	double &operator[](int idx) {  //? 需要传引用吗
		return this->_data[idx];
	}


	double operator[](int idx) const {  //? 需要传引用吗
		return this->_data[idx];
	}
};//vcector 结束

std::ostream &operator<<(std::ostream &os, const Vector &vector) {

	for (int i = 0; i < vector._length; ++i)
		os << vector._data[i] << " ";
	return os;
}

#endif

Vector Vector::INVALID_VECTOR = Vector(0, 0.0); //定义初始化 用于类里面



/*------------------------------
written by Chengwei guo
--------------------------------*/
class Matrix
{
public:
	/// 定义类型便于其他代码使用
	typedef std::vector<Vector> Data;
	/// 定义非法矩阵，这里用0 * 0矩阵表示，也可在Matrix中添加一个特殊标志位
	static Matrix INVALID_MATRIX;

public:
	// Matrix类构造函数.
	/// 默认构造函数要加，否则vector无法resize
	Matrix() {}
	Matrix(const Vector &rhs)
	{
		_row = 1;
		_col = rhs.size();
		_data.push_back(rhs);
	}

	Matrix(int row, int col) { //可以复用 Matrix (row,col,data)
		_row = row;
		_col = col;
		Vector temp(col, 0.0);

		for (int i = 0; i<row; i++) {
			_data.push_back(temp);
		}

	}

	Matrix(int row, int col, const double data[]) //传入数据进行构造 例如：[1,1,1,1] 构造成
	{                                               // [[1,1],[1,1]] 
		_row = row;
		_col = col;
		for (int i = 0; i<row; i++) {
			Vector temp(col, data + i * col);
			_data.push_back(temp);
		}
	}

	Matrix(int row, int col, const double data) {
		_row = row;
		_col = col;
		Vector temp(col, data);
		for (int i = 0; i<row; i++) {
			_data.push_back(temp);
		}
	}

	Matrix(const Matrix &rhs) //拷贝构造
	{
		_row = rhs._row;
		_col = rhs._col;
		_data = rhs._data; // vector<Vector> =
	}

	// Matrix类析构函数
	~Matrix()
	{
		_col = 0;
		_row = 0;
		Data().swap(_data);
	}

	// Matrix类接口.
public:
	// Matrix类私有实现方法
	int rows() {
		return _row;
	}

	int cols() {
		return _col;
	}

private:
	// Matrix类私有属性
	int _row;//行
	int _col;//列
	Data _data;

private:
	/// 所有成员变量应设为私有

	/// operator<<需加友元声明，否则无法打印 
    //暂不实现
	friend std::ostream &operator<<(std::ostream &out, const Matrix &rhs);


public:
	//==
	bool operator==(const Matrix &rhs) {//判断语句
		if ((_col != rhs._col) || (_row != rhs._row)) {
			return false;
		}
		else
		{
			for (int i = 0; i<_row; i++) {
				if (_data[i] != rhs._data[i]) {
					return false;
				}
			}
			return true;
		}
	}

	//!=
	bool operator!=(const Matrix &rhs) {

		return(!(*this == rhs));
	}

	// =
	Matrix operator=(const Matrix &rhs) {//赋值语句 

										 //防止自赋值；
#if 1
		if ((_col != rhs._col) || (_row != rhs._row)) {
			return INVALID_MATRIX;
		}
#endif

		if (&rhs == this) {
			return *this;
		}

		for (int i = 0; i<_row; ++i) {
			_data[i] = rhs._data[i];
		}
		return *this;
	}

	//+
	Matrix operator+(const Matrix &rhs) 
	{//矩阵加法

		if ((_col != rhs._col) || (_row != rhs._row)) {
			return INVALID_MATRIX;
		}
		else {

			Matrix temp(_row, _col);
			for (int i = 0; i <_row; ++i) {
				temp._data[i] = (_data[i] + rhs._data[i]);

			}
			return temp;
		}

	}

	Matrix operator+(const double rhs)
	{//矩阵加法

		Matrix temp(_row, _col, rhs);
		temp = *this + temp; //复用
		return temp;
	}

	//-
	Matrix operator-(const Matrix &rhs)
	{ //矩阵减法
		if ((_col != rhs._col) || (_row != rhs._row)) {
			return INVALID_MATRIX;
		}
		else {
			Matrix temp(_row, _col);
			for (int i = 0; i <_col; ++i) {
				temp._data[i] = (_data[i] - rhs._data[i]);
			}
			return temp;
		}
	}

	//-
	Matrix operator-(const double rhs)
	{ //矩阵    减法

		Matrix temp(_row, _col, rhs);
		temp = *this - temp; //复用
		return temp;
	}

	//*
	Matrix operator*(const double num)
	{ //矩阵对应数乘

		Matrix temp(_row, _col);
		for (int i = 0; i<_row; ++i) {
			temp._data[i] = _data[i] * num;
		}
		return temp;
	}
 
 //矩阵的转置
	Matrix trans() const
	{

		 Matrix temp_trans(_col, _row,0.0);

		for (int i = 0; i<_col; ++i) {
			for (int j = 0; j<_row; ++j) {
				temp_trans._data[i][j] = _data[j][i];
			}
		}
		return temp_trans;
	}

	Matrix operator*( const Matrix rhs) 
	{ //矩阵对应矩阵乘

		if (_col != rhs._row) {
			return INVALID_MATRIX;
		}
		else {
			Matrix left_temp(_row, rhs._col);
			//Matrix temp2(rhs._col, rhs._row);
			//temp2= rhs.trans();
			for (int i = 0; i<_row; ++i) {
				for (int j = 0; j<rhs._col; ++j) {
					left_temp._data[i][j] = _data[i] * rhs.trans()._data[j];
				}
			}
			return left_temp;
		}
	}

	//-负号
	Matrix operator-() {
		Matrix temp(_row, _col);
		for (int i = 0; i<_row; i++) {
			temp._data[i] = -_data[i];
		}
		return temp;
	}
	//[]

	Vector &operator[](int idx) { //行 传引用？
		return _data[idx];
	}

	Vector operator[](int idx) const { //行 传引用？
		return _data[idx];
	}
}; // class Matrix类定义结束.

Matrix Matrix::INVALID_MATRIX = Matrix(0, 0);
/// 定义Matrix流输出操作 
//不实现
std::ostream &operator<<(std::ostream &out, const Matrix &rhs);



// 提供的测试代码
// 该测试用例中涉及的Vector及Matrix自行设计，逐渐熟悉并掌握类接口设计能力
// 建议可以先注释掉全部或大部分测试代码，从而以免在一开始因代码仅完成很少部分，产生太多编译错误
// 仅通过测试代码分析类的职责，开发完成后，放开测试代码
// 测试不通过，在考虑职责分析是否有误解
// 建议思考的方式为“我应该为Vector和Matrix提供什么接口，这些接口应当完成什么功能以满足他们的职责”为出发点，实现后通过测试用例验证
// 而非“我应该为Vector和Matrix提供什么接口，以能通过测试代码”为出发点，通不过一句，改一个函数，通过一句，就转移到下一个函数的方式
// 前者以对象为中心，考虑职责，在思考过程和实现过程中，类独立设计并实现，最终通过交互完成功能，类设计和实现的过程和测试代码的顺序无关，
// 仅与自身从测试代码中分析并融合出的职责需求有关
// 后者以过程为中心，考虑功能，思考过程和实现的过程中，类在不断的“测试过程”中运行，以测试代码运行的顺序增加功能
/*
int main(int argc, char *argv[])
{
    // 通过传递元素素组初始化向量，最终将得到3个元素
    double data1[] = {3.4, 4.4, 6.0};
    Vector v(sizeof(data1) / sizeof(double), data1);

    // 确保完备的初始化向量
    assert(v.size() == sizeof(data1) / sizeof(double));
    for (int idx = 0; idx < sizeof(data1) / sizeof(double); ++idx)
    {
        assert(v[idx] == data1[idx]);
    }

    // v的值应等于自身，且不会不等于自身
    assert(v == v);
    assert(!(v != v));

    // v + v按元素分别求和的结果，相当于每个元素直接与2相乘
    assert(v + v == v * 2);

    // v - v按元素分别求和的结果，相当于v加上v的相反数
    assert(v - v == v + (-v));

    // v = 3的结果使向量的每个元素都变为3，因此等于直接初始化一个只有三个元素，且初始值为3的向量
    assert((v = 3) == Vector(sizeof(data1) / sizeof(double), 3));

    // v + 3的结果使向量的每个元素都加上3，因此等于直接初始化一个只有三个元素，且初始值为6的向量
    // 而 v - 3则直接初始化一个只有三个元素，且初始值为0的向量
    assert(v + 3 == Vector(sizeof(data1) / sizeof(double), 6));
    assert(v - 3 == Vector(sizeof(data1) / sizeof(double), 0.0));

    // 另行定义一个有十个元素，且每个元素值为5的向量
    Vector v2(10, 5);

    // 确保其正确初始化
    assert(v2.size() == 10);
    for (int idx = 0; idx < v2.size(); ++idx)
    {
        assert(v2[idx] == 5);
    }

    // 两个元素个数不相等的向量相加，其结果为【无效向量】
    assert(v + v2 == Vector::INVALID_VECTOR);

    //////////////////////////////////////////////////
    // 通过传递元素素组初始化矩阵，3( 行) X 2(列) 矩阵为：
    // 1 1
    // 1 1
    // 1 1
    double data2[] = {1, 1, 1, 1, 1, 1};
    Matrix m1(3, 2, data2);

    // m4等于m1乘以标量2，因此按元素分别求乘积，得到3( 行) X 2(列) 矩阵，为：
    // 2 2
    // 2 2
    // 2 2
    Matrix m4 = m1 * 2;

    // 确保m1初始化正确，且与标量乘积正确
    assert(m4.rows() == 3);
    assert(m4.cols() == 2);
    for (int r = 0; r < 2; ++r)
    {
        for (int c = 0; c < 2; ++c)
        {
            assert(m4[r][c] == 2);
        }
    }

    // 以同样的数组初始化矩阵，但如果行数、列数不同，获得的矩阵也不同
    Matrix m2(6, 1, data2);
    Matrix m3(3, 2, data2);

    // 因此m1与m2同样有6个1，但行列不同，因此不相等
    assert(m1 != m2);
    // 只有m3这样的行列相同，元素相同，才应相等
    assert(m1 == m3);

    // 同样的结果可以通过直接初始化每个元素为一个相同的数值得到
    assert(m1 == Matrix(3, 2, 1));

    // m1相加之后，应得到一个3行2列，元素全为2的矩阵
    assert(m1 + m1 == Matrix(3, 2, 2));
    // 但如果矩阵行列不同，无法直接相加，只能得到非法矩阵
    assert(m1 + m2 == Matrix::INVALID_MATRIX);

    // 同样，减法按元素相减，相当于加上相反数
    assert(m1 - m1 == m1 + (-m1));
    // 相反数的结果应正确
    assert(-m1 == Matrix(3, 2, -1));

    // 在乘法中，如果矩阵行列不满足条件，只能得到非法矩阵
    assert(m1 * m1 == Matrix::INVALID_MATRIX);
    // 满足乘法条件，m1与其转置矩阵的乘积((3 X 2) X (2 X 3))为3行3列元素为2矩阵
    assert(m1 * m1.trans() == Matrix(3, 3, 2));
    // 满足乘法条件，m1转置矩阵与m1的乘积((2 X 3) X (3 X 2))为2行2列元素为3矩阵
    assert(m1.trans() * m1 == Matrix(2, 2, 3));

    // 向量可转化为矩阵与矩阵相乘，同样要满足矩阵乘法条件，由于v相当于1X3矩阵，元素为3，因此结果为1X2矩阵，元素为9
    assert(Matrix(v) * m1 == Matrix(1, 2, 9));
    // 改变顺序后也可通过转置获得另一个乘积，因此结果为2X1矩阵，元素为9，即相当于上面一个结果的转置
    assert(m1.trans() * Matrix(v).trans() == Matrix(2, 1, 9));
    return 0;
}

*/