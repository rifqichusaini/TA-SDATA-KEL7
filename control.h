#define garis "================================\n"
#define hapus "\033c"
const string pathData = "../data";
const string pathKategori = "../data/kategori";
const string pathCredentials = "../data/credentials";
const string pathFileKategori = "../data/kategori/kategori.txt";
const string pathKeranjang = "../data/keranjang";
const string pathAntrian = "../data/antrian";
const string pathFileAntrian = "../data/antrian/0 - antrian.txt";
const string pathStruk = "../data/struk";

void fetchExBarang(string kategori);
Array1D<string> bacaFolder(string path);

bool konfirmasi(){
  char konf;
  bool isValid = true;
  cout<<"(y/n) > ";
  cin>>konf;
  do{
    if(konf == 'y' || konf == 'Y'){
      return true;
    } else if(konf == 'N' || konf == 'n'){
      return false;
    } else{
      isValid = false;
    }
  } while (!isValid);
  
  return false;
}

int hitungLine(string path){
  ifstream read(path);
  int line = 0;
  string tmp;
  while (getline(read, tmp)){
    line++;
  }
  return line;
}

string getTimestamp() {
  // Mendapatkan waktu saat ini
  auto now = chrono::system_clock::now();
  auto time_t_now = chrono::system_clock::to_time_t(now);
  auto tm_now = *localtime(&time_t_now);

  // Mengonversi waktu ke format yang diinginkan
  stringstream ss;
  ss << put_time(&tm_now, "%Y/%m/%d %H:%M");

  return ss.str();
}

Array1D<string> sortTanggal(Array1D<string> &tanggal){
  // // Urutkan tanggal dari yang terbaru ke yang paling lama
  // sort(tanggal.begin(), tanggal.end(), greater<string>());

  // Urutkan tanggal dari yang paling lama ke yang terbaru 
  sort(tanggal.begin(), tanggal.end(), less<string>());
  return tanggal;
}

void jeda(){
  cout<<"Tekan enter untuk melanjutkan...";
  cin.get();
}

bool cariFolder(string path){
  if(fs::exists(path)){
    return true;
  }
  return false;
}

void createFolder(string path){
  fs::create_directory(path);
}

void input(string &kata) {
  getline(cin, kata);
  if (!kata.empty() && islower(kata[0])) {
    kata[0] = toupper(kata[0]);
  }
}

void cekDB(){
  if (!fs::exists(pathData)) {
    // Membuat folder baru
    createFolder(pathData);
  }

  if (!fs::exists(pathKategori)) {
    createFolder(pathKategori);
  }

  if (!fs::exists(pathKategori+"/kategori.txt")) {
    ofstream fileKategori(pathKategori+"/kategori.txt");
  }
  if (!fs::exists(pathAntrian)) {
    createFolder(pathAntrian);
  }

  if (!fs::exists(pathAntrian+"/0 - antrian.txt")) {
    ofstream fileKategori(pathAntrian+"/0 - antrian.txt");
  }

  if (!fs::exists(pathCredentials)) {
    createFolder(pathCredentials);
  }
  if (!fs::exists(pathAntrian)) {
    createFolder(pathAntrian);
  }
  if (!fs::exists(pathKeranjang)) {
    createFolder(pathKeranjang);
  }
  if (!fs::exists(pathStruk)) {
    createFolder(pathStruk);
  }

  if (!fs::exists(pathCredentials+"/account.txt")) {
    ofstream fileCreds(pathCredentials+"/account.txt");
    fileCreds<<"admin|pass|administrator"<<endl;
  }
  Array1D<string> kategori = bacaFolder(pathKategori);

  for(int i=0;i<kategori.size();i++){
    fetchExBarang(kategori[i]);
  }
}

bool cekKategori(){
  int line = hitungLine(pathFileKategori);
  if(line == 0){
    return false;
  }
  return true;
}

void headerKategori(int sizeKategori = 0){
  if(hitungLine(pathFileKategori) != 0){
    cout<<garis;
    cout<<"== List Kategori yang tersedia =\n";
    cout<<garis;
  }
}

Array2D<string> loadData(string path){
  ifstream file(path);
  Array2D<string> rows;
  string line, item;
  
  while (getline(file, line)) {
    istringstream stream(line);
    Array1D<string> row;
    while (getline(stream, item, '|')) {
      row.push_back(item);
    }
    rows.push_back(row);
  }

  return rows;
}

Array1D<string> bacaFolder(string path) {
  Array1D<string> namaFolder;

  for (const auto& entry : fs::directory_iterator(path)) {
    if (fs::is_directory(entry.status())) {
      namaFolder.push_back(entry.path().filename().string());
    }
  }

  return namaFolder;
}

Array1D<string> bacaFile(string path) {
  Array1D<string> namaFolder;

  for (const auto& entry : fs::directory_iterator(path)) {
    if (fs::is_regular_file(entry.status())) {
      namaFolder.push_back(entry.path().filename().string());
    }
  }

  return namaFolder;
}

void fetchExKategori(){
  Array1D<string> folderNames = bacaFolder(pathKategori);
  ofstream update(pathFileKategori);
  for(int i=0;i<folderNames.size();i++){
    update<<i+1<<"|"<<folderNames[i]<<endl;
  }
}

void fetchExBarang(string kategori) {
  Array1D<string> path;
  Array2D<string> isiFile;
  string pathBuilder;
  string pathFileKategori = pathKategori+"/"+kategori+"/"+kategori+".txt";
  // ganti ke pathFileKategori

  isiFile = loadData(pathFileKategori);

  for(int i=0;i<isiFile.size();i++){
    pathBuilder = "";
    pathBuilder += pathKategori + "/" + isiFile[i][2] + "/barang/" + isiFile[i][1] + ".txt";
    path.push_back(pathBuilder);
  }

  int size = path.size();
  for (int i = size - 1; i >= 0; i--) {
    if (!cariFolder(path[i])) {
      isiFile.erase(isiFile.begin() + i);
      path.erase(path.begin() + i);
    }
  }

  for(int i=0;i<path.size();i++){
    isiFile[i][3] = to_string(hitungLine(path[i]));
  }

  ofstream out(pathFileKategori);
  for(int i=0;i<isiFile.size();i++){
    out<<i+1
    <<"|"<<isiFile[i][1]
    <<"|"<<isiFile[i][2]
    <<"|"<<isiFile[i][3]
    <<"|"<<isiFile[i][4]
    <<endl;
  }
}

// bisa di bypass
template <typename T>
bool inputValidation(T &input) {
  cin >> input;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
  }
  return true;
}

void invalidInput(){
  cout<<"Masukkan angka bukan karakter!\n";
  jeda();
}

// void vec2dToArr2d(const Array2D<string> &vec2d, string **&arr2d) {
//     // Tentukan ukuran baris dan kolom
//     int baris = vec2d.size();
//     int kolom = baris > 0 ? vec2d[0].size() : 0;

//     // Alokasi memori untuk array 2D dinamis
//     arr2d = new string *[baris];
//     for (int i = 0; i < baris; ++i) {
//         arr2d[i] = new string[kolom];
//     }

//     // Salin nilai dari Array1D ke array 2D
//     for (int i = 0; i < baris; ++i) {
//         for (int j = 0; j < kolom; ++j) {
//             arr2d[i][j] = vec2d[i][j];
//         }
//     }
// }

// void vecToArr(const Array1D<string> &vec, string *&arr) {
//     // Tentukan ukuran array
//     int ukuran = vec.size();

//     // Alokasi memori untuk array dinamis
//     arr = new string[ukuran];

//     // Salin nilai dari Array1D ke array 1D
//     for (int i = 0; i < ukuran; ++i) {
//         arr[i] = vec[i];
//     }
// }

