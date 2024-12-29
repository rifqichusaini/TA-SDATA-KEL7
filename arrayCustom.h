template <typename T>
class Array1D{
private:
  T* arr;
  int ukuran;  

public:
  using iterator = T*;

  iterator end() { return arr + ukuran; }
  
  iterator begin() { return arr; }

  iterator erase(iterator posisi) {
  if (posisi < begin() || posisi >= end()) {
    throw out_of_range("Iterator diluar batas!");
  }
  
  // temp adalah posisi hapus
  // lalu temp akan ditimpa dengan temp + 1.
  iterator temp = posisi;
  while (temp != end() - 1) {
    *temp = *(temp + 1);
    ++temp;
  }
  --ukuran;
  return posisi;
  }

  // default construktor, pembentukan dasar array
  Array1D() : arr(new T[0]), ukuran(0) {}

  // deklarasi array dengan inisialisasi, contoh -> Array1D<int> testArr = {1,3,4};
  Array1D(initializer_list<T> list) : arr(new T[list.size()]), ukuran(0){
  for(auto& isiList : list){
    arr[ukuran++] = isiList;
  }
  }
  // Tambahkan const pada method-method yang tidak mengubah objek
  int size() const { return ukuran; }

  // Tambahkan const operator[]
  const T& operator[](int index) const {
    if (index < 0 || index >= ukuran) {
      throw out_of_range("Index di luar batas");
    }
    return arr[index];
  }

  // isi array, contoh -> testArr = {1,3,4};
  Array1D &operator=(initializer_list<T> list){
  // Hapus array lama
  delete[] arr;
  
  // Set ukuran baru
  ukuran = list.size();
  
  // Alokasi array baru
  arr = new T[ukuran];
  
  // Salin menggunakan iterator
  int i = 0;
  for(auto& item : list){
    arr[i++] = item;
  }
  
  return *this;
}

  Array1D& operator=(const Array1D<T>& other) {
  if(this != &other) {
    delete[] arr;
    ukuran = other.ukuran;
    arr = new T[ukuran];
    for(int i = 0; i < ukuran; i++) {
      arr[i] = other[i];
    }
  }
  return *this;
  }

  // Tambahkan copy constructor
  Array1D(const Array1D<T>& other) : arr(new T[other.ukuran]), ukuran(other.ukuran) {
    for(int i = 0; i < ukuran; i++) {
      arr[i] = other[i];
    }
  }

  // copy array, contoh -> arr1 = arr2;
  Array1D &operator=(Array1D<T>& other){
  if(this != &other){
    ukuran = other.ukuran;
    delete[] arr;
    arr = new T[ukuran];
    for(int i=0;i<ukuran;i++){
    arr[i] = other[i];
    }
  }
  return *this;
  }


  void push_back(T dataBaru){
  // Alokasi array baru dengan ukuran bertambah
  T* newArr = new T[ukuran + 1];
  
  // Salin elemen lama jika ada
  for(int i = 0; i < ukuran; i++){
    newArr[i] = arr[i];
  }
  
  // Tambahkan elemen baru
  newArr[ukuran] = dataBaru;
  
  // Hapus array lama hanya jika bukan nullptr
  if (arr != nullptr) {
    delete[] arr;  // Perhatikan penggunaan delete[]
  }
  
  // Update pointer dan ukuran
  arr = newArr;
  ukuran++;
}

  // menghapus element dari belakang
  void pop_back(){
  T* newArr = new T[ukuran - 1];
  for(int i=0;i<ukuran-1;i++){
    newArr[i] = arr[i];
  }
  delete[] arr;

  arr = newArr;
  ukuran--;
  }

  // operator untuk mengakses array secara langsung, contoh -> arr1[1];
  T& operator[](int index) {
    if (index < 0 || index >= ukuran) {
      throw out_of_range("Index di luar batas");
    }
    return arr[index];
  }

  // mengembalikan ukuran array
  int size(){ return ukuran; }

  // mengembalikan ukuran array
  int length(){ return ukuran; }

};

template <typename T>
class Array2D {
private:
  T** arr;
  int* kolom_sizes;  // Array untuk menyimpan ukuran setiap baris
  int baris;

public:
  // Default constructor
  Array2D() : arr(nullptr), kolom_sizes(nullptr), baris(0) {}

  // Constructor with initializer list
  Array2D(initializer_list<initializer_list<T>> list) : baris(list.size()) {
    arr = new T*[baris];
    kolom_sizes = new int[baris];  // Alokasi array untuk ukuran kolom
    
    // Inisialisasi setiap baris
    int i = 0;
    for (const auto& isiBaris : list) {
      kolom_sizes[i] = isiBaris.size();  // Simpan ukuran kolom untuk baris ini
      arr[i] = new T[kolom_sizes[i]];
      
      // Salin data
      int j = 0;
      for (const auto& isiKolom : isiBaris) {
        arr[i][j++] = isiKolom;
      }
      i++;
    }
  }

  Array2D& operator=(initializer_list<initializer_list<T>> list) {
    // Hapus data lama jika ada
    if (arr != nullptr) {
      for (int i = 0; i < baris; i++) {
        delete[] arr[i];
      }
      delete[] arr;
      delete[] kolom_sizes;
    }

    // Set ukuran baru
    baris = list.size();
    
    // Alokasi memori baru
    arr = new T*[baris];
    kolom_sizes = new int[baris];
    
    // Salin data baru
    int i = 0;
    for (const auto& isiBaris : list) {
      kolom_sizes[i] = isiBaris.size();
      arr[i] = new T[kolom_sizes[i]];
      
      int j = 0;
      for (const auto& isiKolom : isiBaris) {
        arr[i][j++] = isiKolom;
      }
      i++;
    }
    
    return *this;
  }

  class Baris {
  private:
    T* baris;
    int& ukuran_kolom;

  public:
    Baris(T* r, int& cs) : baris(r), ukuran_kolom(cs) {}

    T& operator[](int kolom) {
      if (kolom >= ukuran_kolom) {
        throw out_of_range("index colom diluar batas!");
      }
      return baris[kolom];
    }

    using iterator = T*;

    iterator begin() { return baris; }
    iterator end() { return baris + ukuran_kolom; }
    int size() const { return ukuran_kolom; }
    T* getData() { return baris; }

    iterator erase(iterator posisi) {
      if (posisi < begin() || posisi >= end()) {
        throw out_of_range("Iterator diluar batas!");
      }

      // Geser elemen-elemen ke kiri
      for(iterator it = posisi; it < end() - 1; ++it) {
        *it = *(it + 1);  // Timpa elemen sekarang dengan elemen berikutnya
      }
      
      // Set elemen terakhir ke nilai default
      *(end() - 1) = T();
      
      // Kurangi ukuran
      --ukuran_kolom;
      
      return posisi;
    }

    operator Array1D<T>() const {
      Array1D<T> result;
      for(int i = 0; i < ukuran_kolom; i++) {
        result.push_back(baris[i]);
      }
      return result;
    }
  };

  Baris operator[](int index_baris) {
    if (index_baris >= baris) {
      throw out_of_range("index row diluar batas!");
    }
    return Baris(arr[index_baris], kolom_sizes[index_baris]);
  }

  int size() const { return baris; }
  
  using iterator = T**;
  iterator begin() { return arr; }
  iterator end() { return arr + baris; }

  iterator erase(iterator posisi) {
    if (posisi < begin() || posisi >= end()) {
      throw out_of_range("Iterator diluar batas!");
    }

    // Simpan pointer ke baris yang akan dihapus
    T* rowToDelete = *posisi;
    int* sizeToDelete = &kolom_sizes[posisi - begin()];

    // Geser pointer baris dan ukuran kolom
    for (int i = posisi - begin(); i < baris - 1; i++) {
      arr[i] = arr[i + 1];
      kolom_sizes[i] = kolom_sizes[i + 1];
    }

    // Hapus baris yang sudah tidak terpakai
    delete[] rowToDelete;

    // Kurangi jumlah baris
    baris--;

    return posisi;
  }
  
  // Metode insert untuk menambahkan baris baru di posisi tertentu dari Array1D
  void insert(iterator posisi, const Array1D<T>& copyElement) {
    // Alokasi memori baru dengan jumlah baris bertambah
    T** new_arr = new T*[baris + 1];
    int* new_kolom_sizes = new int[baris + 1];

    // Hitung posisi insert
    int insert_index = posisi - begin();

    // Salin baris sebelum posisi insert
    for (int i = 0; i < insert_index; i++) {
      new_arr[i] = arr[i];
      new_kolom_sizes[i] = kolom_sizes[i];
    }

    // Buat baris baru
    new_kolom_sizes[insert_index] = copyElement.size();
    new_arr[insert_index] = new T[copyElement.size()];

    // Salin elemen ke baris baru
    for (int j = 0; j < copyElement.size(); j++) {
      new_arr[insert_index][j] = copyElement[j];
    }

    // Salin baris setelah posisi insert
    for (int i = insert_index; i < baris; i++) {
      new_arr[i + 1] = arr[i];
      new_kolom_sizes[i + 1] = kolom_sizes[i];
    }

    // Hapus array lama
    delete[] arr;
    delete[] kolom_sizes;

    // Update pointer
    arr = new_arr;
    kolom_sizes = new_kolom_sizes;
    baris++;
  }

  // push_back back untuk menambah baris baru dari Array1D
  void push_back(const Array1D<T>& newRow) {
    // Buat array baru dengan ukuran baris + 1
    T** new_arr = new T*[baris + 1];
    int* new_kolom_sizes = new int[baris + 1];
    
    // Salin array lama
    for(int i = 0; i < baris; i++) {
      new_arr[i] = arr[i];
      new_kolom_sizes[i] = kolom_sizes[i];
    }
    
    // Tambah baris baru
    new_kolom_sizes[baris] = newRow.size();
    new_arr[baris] = new T[newRow.size()];
    
    // Salin data dari Array1D ke baris baru
    for(int i = 0; i < newRow.size(); i++) {
      new_arr[baris][i] = newRow[i];
    }
    
    // Hapus array pointer lama
    delete[] arr;
    delete[] kolom_sizes;
    
    // Update pointer dan ukuran
    arr = new_arr;
    kolom_sizes = new_kolom_sizes;
    baris++;
  }

  // pop_back back untuk menghapus baris terakhir
  void pop_back() {
    if(baris == 0) {
      throw out_of_range("Array kosong");
    }
    
    // Hapus baris terakhir
    delete[] arr[baris - 1];
    
    // Buat array baru dengan ukuran baris - 1
    T** new_arr = new T*[baris - 1];
    int* new_kolom_sizes = new int[baris - 1];
    
    // Salin semua baris kecuali yang terakhir
    for(int i = 0; i < baris - 1; i++) {
      new_arr[i] = arr[i];
      new_kolom_sizes[i] = kolom_sizes[i];
    }
    
    // Hapus array pointer lama
    delete[] arr;
    delete[] kolom_sizes;
    
    // Update pointer dan ukuran
    arr = new_arr;
    kolom_sizes = new_kolom_sizes;
    baris--;
  }
};