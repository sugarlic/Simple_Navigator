#include "../includes/matrix.h"

S21Matrix::S21Matrix() : matrix_{nullptr}, rows_{1}, cols_{1} {
  MatrixMemoryReallocating(1, 1);
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument("Incorrect data to allocate matrix.");
  this->cols_ = cols;
  this->rows_ = rows;
  this->matrix_ = nullptr;
  MatrixMemoryReallocating(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : matrix_{nullptr}, rows_{other.rows_}, cols_{other.cols_} {
  MatrixMemoryReallocating(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : matrix_{nullptr}, rows_{0}, cols_{0} {
  std::swap(cols_, other.cols_);
  std::swap(rows_, other.rows_);
  std::swap(matrix_, other.matrix_);
}

S21Matrix::~S21Matrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++)
      if (this->matrix_[i] != nullptr) delete[] this->matrix_[i];
    delete[] this->matrix_;
  }
}

void S21Matrix::MatrixMemoryReallocating(int new_row, int new_col) {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++)
      if (matrix_[i] != nullptr) delete[] matrix_[i];
    delete[] this->matrix_;
  }

  matrix_ = new double*[new_row];
  for (int i = 0; i < new_row; i++) {
    matrix_[i] = new double[new_col]{};
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("No equal matrix");
  S21Matrix result(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("No equal matrix");
  S21Matrix result(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (this->cols_ != other.rows_)
    throw std::invalid_argument("No equal matrix");
  S21Matrix result(this->cols_, other.rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result = *this;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] *= num;
    }
  }
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  bool isEqual = false;
  if ((other.cols_ == cols_) && (other.rows_ == rows_)) {
    isEqual = true;
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) isEqual = false;
      }
    }
  }
  return isEqual;
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix::MatrixMemoryReallocating(other.rows_, other.cols_);
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) this->matrix_[i][j] = other.matrix_[i][j];
  return *this;
}

S21Matrix S21Matrix::operator=(S21Matrix&& other) {
  if (this == &other) return *this;
  for (int i = 0; i < rows_; i++) {
    if (matrix_[i]) {
      delete[] matrix_[i];
    }
  }
  if (matrix_) {
    delete[] matrix_;
    matrix_ = nullptr;
  }
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
  return *this;
}

void S21Matrix::operator+=(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("No equal matrix");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::operator-=(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("No equal matrix");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::operator*=(const S21Matrix& other) {
  S21Matrix tmp_matrix(this->rows_, other.cols_);
  if (this->cols_ != other.rows_)
    throw std::invalid_argument("Incorrect matrix");
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        tmp_matrix.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp_matrix;
}

void S21Matrix::operator*=(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

double& S21Matrix::operator()(int i, int j) {
  if ((i >= this->rows_ || j >= this->cols_) || (i < 0 || j < 0))
    throw std::invalid_argument("Invalid argument");
  return this->matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  if ((i >= this->rows_ || j >= this->cols_) || (i < 0 || j < 0))
    throw std::invalid_argument("Invalid argument");
  return this->matrix_[i][j];
}

bool S21Matrix::EqMatrix(const S21Matrix& other) { return (*this == other); }

void S21Matrix::SumMatrix(const S21Matrix& other) { *this += other; }

void S21Matrix::SubMatrix(const S21Matrix& other) { *this -= other; }

void S21Matrix::MulNumber(const double num) { *this *= num; }

void S21Matrix::MulMatrix(const S21Matrix& other) { *this *= other; }

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = this->matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_)
    throw std::invalid_argument("Matrix is not square");
  S21Matrix minor(rows_ - 1, cols_ - 1);
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      minor = CreateMinor(i, j);
      result.matrix_[i][j] = pow(-1, i + j) * minor.Determinant();
      minor.ClearMatrix();
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (this->cols_ != this->rows_)
    throw std::invalid_argument("Matrix is not square.");
  if (this->rows_ == 1 && this->cols_) return this->matrix_[0][0];
  if (this->rows_ == 2 && this->cols_ == 2)
    return (this->matrix_[0][0] * this->matrix_[1][1] -
            this->matrix_[0][1] * this->matrix_[1][0]);
  S21Matrix new_matrix(this->rows_ - 1, this->cols_ - 1);
  double result = 0;
  S21Matrix minor;
  for (int i = 0; i < cols_; i++) {
    minor = CreateMinor(0, i);
    result += matrix_[0][i] * pow(-1, i) * minor.Determinant();
    minor.ClearMatrix();
  }
  return result;
}

S21Matrix S21Matrix::CreateMinor(int row, int col) {
  int dst_row = 0, dst_col = 0;
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != col) {
        result(dst_row, dst_col++) = matrix_[i][j];
        if (dst_col == cols_ - 1) {
          dst_row++;
          dst_col = 0;
        }
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (!this->Determinant()) throw std::invalid_argument("Determinant is zero!");
  S21Matrix result = S21Matrix(rows_, cols_);
  S21Matrix minor_matrix = CalcComplements();
  minor_matrix = minor_matrix.Transpose();
  result = minor_matrix * (1 / Determinant());
  return result;
}

int S21Matrix::GetRows() const { return this->rows_; }

int S21Matrix::GetCols() const { return this->cols_; }

void S21Matrix::SetRows(const int rows) {
  if (rows <= 0)
    throw std::invalid_argument("Row value should be more, than 0!");
  S21Matrix copied_matrix(*this);
  MatrixMemoryReallocating(rows, cols_);
  rows_ = rows;
  CopyMatrix(copied_matrix);
}

void S21Matrix::SetCols(const int cols) {
  if (cols <= 0)
    throw std::invalid_argument("Col value should be more, than 0!");
  S21Matrix copied_matrix(*this);
  MatrixMemoryReallocating(rows_, cols);
  cols_ = cols;
  CopyMatrix(copied_matrix);
}

void S21Matrix::ClearMatrix() {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::CopyMatrix(S21Matrix matrix) {
  int new_row = (this->rows_ > matrix.rows_) ? matrix.rows_ : rows_;
  int new_col = (this->cols_ > matrix.cols_) ? matrix.cols_ : cols_;
  for (int i = 0; i < new_row; i++) {
    for (int j = 0; j < new_col; j++) {
      matrix_[i][j] = matrix.matrix_[i][j];
    }
  }
}
