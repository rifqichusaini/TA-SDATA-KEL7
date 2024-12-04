void panjangLebar(Array2D<string> &vec, Array1D<int> &maxCol, int &konstanta){
  int baris = vec.size();
  int kolom = vec[0].size();

  for(int i=0;i<baris;i++){
    for(int j=0;j<kolom;j++){
      if(maxCol[j] < vec[i][j].length()){
        maxCol[j] = vec[i][j].length();
      }
    }
  }
  for(int i=0; i<maxCol.size();i++){
    if(i < maxCol.size() - 1){
      konstanta += 3;
    }
  }
}

void printGaris(Array1D<int> &maxCol, int konstanta){
  for(int i=0;i<maxCol.size();i++){
    konstanta += maxCol[i];
  }
  for(int j=0;j<konstanta;j++){
    cout<<"-";
  }
  cout<<endl;
}

void printData(Array2D<string> &vec, Array1D<string> &col, Array1D<int> &maxCol, int konstanta) {
  int baris = vec.size();
  int kolom = vec[0].size();
  cout<<"| ";
  for(int i=0; i<col.size();i++){
    cout<<setw(maxCol[i])<<col[i];
    if(i < col.size() - 1){
      cout<<" | ";
    }
  }
  cout<<" |"<<endl;

  printGaris(maxCol, konstanta);

  for(int i=0;i<baris;i++){
    cout<<"| ";
    for(int j=0;j<kolom;j++){
      cout<<setw(maxCol[j])<<vec[i][j];
      if(j < kolom - 1){
        cout<<" | ";
      }
    }
    cout<<" |";
    cout<<endl;
  }
}

string getKategori(){
  fetchExKategori();  
  ifstream file(pathFileKategori);
  string kategori, id, line;
  int banyakKategori = hitungLine(pathFileKategori);
  bool isInpuValid = true;
  int pilihan;

  do{
    do{
      cout<<hapus;
      if(hitungLine(pathFileKategori) != 0){
        headerKategori();
      }
      int konstanta = 4;
      Array1D<int> maxCol = {2,8};
      Array1D<string> col = {"id","kategori"};
      Array2D<string> row = loadData(pathFileKategori);
      panjangLebar(row, maxCol, konstanta);
      printGaris(maxCol, konstanta);
      printData(row, col, maxCol, konstanta);
      printGaris(maxCol, konstanta);

      file.close();
      cout<<"pilih id kategori : ";
      if(inputValidation(pilihan)){
        file.open(pathFileKategori);
        if(pilihan <= banyakKategori && pilihan >= 1){
          while (getline(file, line)){
            istringstream stream(line);
            getline(stream, id, '|');
            getline(stream, kategori);
            if(id == to_string(pilihan)){
              return kategori;
            }
          }
        } else{
          cin.ignore();
          cout<<"Pilihan tidak ada!"<<endl;
          jeda();
        }
      } else{
        isInpuValid = false;
        invalidInput();
      }
    } while (!isInpuValid);
  }while (pilihan > banyakKategori || pilihan < 1);
  return "";
}

void getBarang(string barang, string jenis){
  string path = pathKategori;
  path += jenis + "/" + barang + ".txt";
  
  ifstream file(path);
  string line;
  string id, tanggal;
  
  int konstanta = 4;
  Array1D<int> maxCol = {2,7};
  Array1D<string> col = {"id","tanggal"};
  Array2D<string> row = loadData(path);
  panjangLebar(row, maxCol, konstanta);
  printGaris(maxCol, konstanta);
  printData(row, col, maxCol, konstanta);
  printGaris(maxCol, konstanta);
}

string getJenis(string jenis){
  string path = pathKategori;
  path += jenis + "/" + jenis + ".txt";

  ifstream file(path);
  string barang, line, harga, id, pilihan;
  
  int konstanta = 4;
  Array1D<int> maxCol = {2,6,5};
  Array1D<string> col = {"id","barang","harga"};
  Array2D<string> row = loadData(path);
  panjangLebar(row, maxCol, konstanta);
  printGaris(maxCol, konstanta);
  printData(row, col, maxCol, konstanta);
  printGaris(maxCol, konstanta);
  
  file.close();
  cout<<"pilih id barang : ";
  cin>>pilihan;
  file.open(path);
  while (getline(file, line)){
    istringstream stream(line);
    getline(stream, id, '|');
    getline(stream, barang, '|');
    getline(stream, harga);
    if(id == pilihan){
      return barang;
    } else{
      cout<<"pilihan tidak ada";
    }  
  }
  return "";
}

void dataUserKosong(){
  cout<<hapus;
  cout<<garis;
  cout<<"===== Database Masih kosong ====\n";
  cout<<garis;
  cout<<"silahkan tunggu admin mengisi barang!\n";
  cout<<garis;
  cin.ignore();
  jeda();
}

void dataKosong(){
  cout<<hapus;
  cout<<garis;
  cout<<"===== Database Masih kosong ====\n";
  cout<<garis;
  cin.ignore();
  jeda();
}

