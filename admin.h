bool cekExBarang(const string& kategori, const string& namaBarang, Array2D<string> dataBarang) {
  Array1D<string> exKategori = bacaFolder(pathKategori);
  for(int i=0;i<exKategori.size();i++){
    if(namaBarang == exKategori[i]){
      cout << garis;
      cout << "Masukan Nama Barang,\nBukan Kategori Barang!\n";
      cout << garis;
      jeda();
      return false;
    }
  }

  string path = pathKategori+"/"+kategori+"/barang/"+namaBarang+".txt";
  if (fs::exists(path)) {
    cout << garis;
    cout << "Barang sudah ada!,\nSilakan masuk ke menu update\n"
        "jika Anda ingin mengupdate data!\n";
    cout << garis;
    jeda();
    return false;
  }  

  for(int i=0;i<dataBarang.size();i++){
    if(dataBarang[i][0] == namaBarang && dataBarang[i][1] == kategori){
      cout << garis;
      cout<<"tidak boleh memasukkan barang yang sama\n"
        "Terjadi duplikasi data!\n";
      cout << garis;
      jeda();
      return false;
    }
  }
  return true;
}

void outBarang(Array2D<string> &vec, bool id = false, bool colKategori = false, bool totalHarga = false) {
  int konstanta = 4;
  Array1D<int> maxCol;
  Array1D<string> col;
  if(totalHarga){
    maxCol = {4,8,6,11};
    col = {"Nama","Kategori","Jumlah","Total Harga"};
  } else if(id){
    maxCol = {2,4,8,6,5};
    col = {"id", "Nama","Kategori","Jumlah","Harga"};
  } else if(colKategori){
    maxCol = {4,6,5};
    col = {"Nama","Jumlah","Harga"};
  } else{
    maxCol = {4,8,6,5};
    col = {"Nama","Kategori","Jumlah","Harga"};
  }
  panjangLebar(vec, maxCol, konstanta);
  printGaris(maxCol, konstanta);
  printData(vec, col, maxCol, konstanta);
  printGaris(maxCol, konstanta);
}

bool cekExKategori(string path, Array2D<string> newKategori, string kategori){
  if(cariFolder(path)){
    cout<<"KATEGORI SUDAH ADA!, SILAHKAN MASUKKAN YANG BARU!"<<endl;
    cout<<garis;
    jeda();
    return false;
  }

  for(int i=0;i<newKategori.size();i++){
    if(kategori == newKategori[i][0]){
      cout<<"tidak boleh memasukkan barang yang sama\n"
        "Terjadi duplikasi data!\n";
      cout << garis;
      jeda();
      return false;
    }
  }
  return true;
}

void outKategori(Array2D<string> &vec){
  int konstanta = 4;
  Array1D<int> maxCol = {8};
  Array1D<string> col = {"Kategori"};
  panjangLebar(vec, maxCol, konstanta);
  printGaris(maxCol, konstanta);
  printData(vec, col, maxCol, konstanta);
  printGaris(maxCol, konstanta);
}

void tambahBarang() {
  cout<<hapus;
  char konf;
  Array2D<string> dataBarang;
  Array2D<string> exBarang;
  string pilKategori;
  string namaBarang;
  string hargaBarang;
  int jmlBarang;
  // Array1D<string> tanggalBarang;
  Array1D<string> path;
  
  do{  
    Array1D<string> detailBarang;
    do{
      int x = hitungLine(pathFileKategori);
      if(hitungLine(pathFileKategori) != 0){
        cout<<hapus;
        cout << garis;
        cout << "Pilih kategori barang baru" << endl;
        cout << garis;
        pilKategori = getKategori();
        string tmp = pathKategori+"/"+pilKategori+"/"+pilKategori+".txt";
        cout<<hapus;
        if(dataBarang.size() != 0){        
          cout<<garis;
          cout<<"List barang yang sudah diinput\n";
          cout<<garis;
          outBarang(dataBarang);
        } if(hitungLine(tmp) != 0){
          cout<<garis;
          cout<<"Barang yang sudah tersedia di "<<pilKategori<<endl;
          cout<<garis;
          exBarang = loadData(tmp);
          for(int i=0;i<exBarang.size();i++){
            exBarang[i].erase(exBarang[i].begin() + 0);
            exBarang[i].erase(exBarang[i].begin() + 1);
          }
          outBarang(exBarang, false, true);
        } if(hitungLine(tmp) == 0 && dataBarang.size() == 0){
          cout<<garis;
          cout<<"Barang di "<<pilKategori<<" masih kosong.\n";
          cout<<garis;
        }
        cin.ignore();
        cout << "Masukkan Nama barang baru di "<<pilKategori<<" : ";
        input(namaBarang);
      } else{
        cout<<garis;
        cout<<"Data Kategori Kosong!\nsilahkan isi data kategori terlebih dahulu!"<<endl;
        cout<<garis;
        cin.ignore();
        jeda();
        return;
      }
    }while(!cekExBarang(pilKategori, namaBarang, dataBarang));

// inputValidation();
    cout << "Masukkan Harga satuan " << namaBarang << " : ";
    getline(cin, hargaBarang);

    cout << "Masukkan jumlah " << namaBarang << " : ";
    cin >> jmlBarang;
    cin.ignore();

    detailBarang.push(namaBarang);
    detailBarang.push(pilKategori);
    detailBarang.push(to_string(jmlBarang));
    detailBarang.push(hargaBarang);
    // push ke 2d
    dataBarang.push(detailBarang);
    cout<<hapus;
    cout<<garis;
    cout<<"==== DATA INPUT BARANG BARU ===="<<endl;
    cout<<garis;
    outBarang(dataBarang);
    cout<<"tambah data lagi ?\n(y/n) > ";
    cin>>konf;
  }while (konf == 'y');
  do{
    cout<<hapus;
    cout<<garis;
    cout<<"==== DATA INPUT BARANG BARU ===="<<endl;
    cout<<garis;
    outBarang(dataBarang);

    cout<<"simpan data ke database?\n(y/n) > ";
    cin>>konf;

    if(konf == 'y'){
      int k = 0;
    
      for(int i = 0;i<dataBarang.size();i++){
        fetchExBarang(dataBarang[i][1]);

        path.push(pathKategori+"/" + dataBarang[i][1] + "/barang/" + dataBarang[i][0] + ".txt");
        ofstream outIsiBarang(path[i]);
        for(int j=0;j<stoi(dataBarang[i][2]);j++){
          // outIsiBarang<<j+1<<"|"<<tanggalBarang[k]<<endl;
          outIsiBarang<<j+1<<endl;
          k++;
        }
        outIsiBarang.close();

        path.push(pathKategori+"/" + dataBarang[i][1] + "/" + dataBarang[i][1] + ".txt");
        
        ofstream outKategori(path[path.size()-1], ios::app);
        int jmlBarang = hitungLine(pathKategori+"/" + dataBarang[i][1] + "/" + dataBarang[i][1] + ".txt");

        outKategori<<jmlBarang+1
          <<"|"<<dataBarang[i][0]
          <<"|"<<dataBarang[i][1]
          <<"|"<<dataBarang[i][2]
          <<"|"<<dataBarang[i][3]
        <<endl;
        outKategori.close();
        path.pop();
      }
      cout<<"data berhasil di simpan!"<<endl;
      cin.ignore();
      jeda();
    } else {
      cout<<"data tidak akan tersimpan\n"
      "apakah anda yakin tidak ingin menyimpan?\n(y/n) > ";
      cin>>konf;
    }
  } while (konf == 'n');
}

void tambahKategori(){
  fetchExKategori();
  int jmlKategori;
  char konf;

  cin.ignore();
  string path;
  Array1D<string> newKategoriTmp;
  Array1D<string> newPath;
  Array2D<string> exKategori = loadData(pathFileKategori);
  for(int i=0;i<exKategori.size();i++){
    exKategori[i].erase(exKategori[i].begin() + 0);
  }
  Array2D<string> newKategori;
  string kategori;
  bool isValid;
  do{
    do{
      cout<<hapus;
      cout<<garis;
      if(newKategori.size() != 0){        
        cout<<"== List Kategori yang diinput ==\n";
        cout<<garis;
        outKategori(newKategori);
      }
       if(hitungLine(pathFileKategori) != 0){
        cout<<"= List Kategori yang sudah ada =\n";
        cout<<garis;
        outKategori(exKategori);
      } 
      if(hitungLine(pathFileKategori) == 0 && newKategori.size() == 0){
        cout<<"===== Kategori Masih kosong ====\n";
      }
      path = pathKategori;
      cout<<garis;
      cout<<"masukkan nama kategori baru : ";
      input(kategori);
      newPath.push(path+="/" + kategori);
      cout<<garis;
      newKategoriTmp.push(kategori);
      isValid = cekExKategori(path, newKategori, kategori);
      if(!isValid){
        newPath.pop();
      } else{
        newKategori.push(newKategoriTmp);
      }
      newKategoriTmp.pop();
    } while (!isValid);
    
    cout<<"tambah data lagi?\n(y/n) > ";
    cin>>konf;
    cin.ignore();
  }while (konf == 'y');
  do{
    cout<<hapus;
    cout<<garis;
    cout<<"====== DATA KATEGORI BARU ======"<<endl;
    cout<<garis;
    outKategori(newKategori);

    cout<<"simpan data ke database?\n(y/n) > ";
    cin>>konf;

    if(konf == 'y' || konf == 'Y'){
      for(int i=0;i<newKategori.size();i++){
        for(int j=0;j<newKategori[i].size();j++){
          createFolder(newPath[i]);
          ofstream out(newPath[i]+"/"+newKategori[i][j]+".txt");
          createFolder(newPath[i]+"/barang");
          ofstream addKategori(pathFileKategori, ios::app);
          if(addKategori.is_open()){
            jmlKategori = hitungLine(pathFileKategori);

            jmlKategori++;
            addKategori<<jmlKategori<<"|"<<newKategori[i][j]<<endl;
          }

          if(cariFolder(newPath[i])){
            cout<<newKategori[i][j]<<" Berhasil ditambahkan!"<<endl;
          } else{
            cout<<newKategori[i][j]<<" gagal ditambahkan!"<<endl;
          }
        }
      }
      break;
    } else {
      cout<<"data tidak akan tersimpan\n"
      "apakah anda yakin tidak ingin menyimpan?\n(y/n) > ";
      cin>>konf;
    }
  } while (konf == 'n');
  
  cin.ignore();
  jeda();
}

void autoListAll(){
  fetchExKategori();
  Array1D<string> pathBuilder;
  string path;
  Array2D<string> kategori;
  Array2D<string> barang;
  int line=0;

  if(hitungLine(pathFileKategori)!=0){
    cout<<hapus;
    kategori = loadData(pathFileKategori);
    for(int i=0;i<kategori.size();i++){
      kategori[i].erase(kategori[i].begin() + 0);
    }
    for(int i=0;i<kategori.size();i++){
      path = pathKategori + "/" + kategori[i][0] + "/" + kategori[i][0] + ".txt"; 
      pathBuilder.push(path);
    }
    for(int i=0;i<pathBuilder.size();i++){
      line += hitungLine(pathBuilder[i]);
    }
    if(line != 0){
      for(int i=0;i<pathBuilder.size();i++){
        Array2D<string> data = loadData(pathBuilder[i]);
        // Menggunakan push untuk menambahkan elemen-elemen dari data ke barang
        for (int j = 0; j < data.size(); j++) {
          barang.push(data[j]);
        }
      }
      for(int i=0;i<barang.size();i++){
        barang[i].erase(barang[i].begin() + 0);
      }
      cout<<garis;
      cout<<"List semua barang yang tersedia di database\n";
      cout<<garis;
      outBarang(barang);
      cin.ignore();
      jeda();
    } else{
      dataKosong();
    }
  } else {
    dataKosong();
  }
}


void hapusBarang(){
  string pilihan;
  string kategori;
  string path;
  string pathBarang;
  Array2D<string> barang;
  bool isLoop = false;
  if(hitungLine(pathFileKategori)!=0){
    do{
      kategori = getKategori();
      path = pathKategori + "/" + kategori + "/" + kategori + ".txt";
      if(hitungLine(path) != 0){
        barang = loadData(path);
      
        outBarang(barang, true);
        cout<<"pilih id barang yg ingin dihapus : ";
        cin>>pilihan;

        if(stoi(pilihan) <= 0 || stoi(pilihan) > hitungLine(path)){
          cout<<"masukkan id yang sesuai dengan tabel\n";
          isLoop = true;
          cin.ignore();
          jeda();
        } else{
          for(int i=0;i<barang.size();i++){
            if(pilihan == barang[i][0]){
              cout<<"apakah anda yakin ingin menghapus "
                <<barang[i][1]
                <<" ?\nanda tidak bisa mengembalikan data yang sdh di hapus\n(y/n) > ";
              cin>>pilihan;
              if(pilihan == "y" || pilihan == "Y"){
                cout<<barang[i][1]<<" telah berhasil di hapus!"<<endl;
                pathBarang = pathKategori + "/" + kategori + "/barang/" + barang[i][1] + ".txt";
                barang.erase(barang.begin() + i);
                ofstream update(path);
                for(int j=0;j<barang.size();j++){
                  update<<j+1<<"|"<<barang[j][1]<<"|"
                    <<barang[j][2]<<"|"<<barang[j][3]<<"|"
                    <<barang[j][4]<<endl;
                }
                remove(pathBarang.c_str());
                cin.ignore();
                jeda();
              }
            }
          }
        }
      } else{
        dataKosong();
      }
    } while (isLoop);
  } else{
    dataKosong();
  }
}

void hapusKategori(){
  if(hitungLine(pathFileKategori) != 0){
    string kategori = getKategori();
    string path = pathKategori + "/" + kategori + "/" + kategori + ".txt";
    string pathHapus = pathKategori + "/" + kategori;
    string konf;
    Array2D<string> barang = loadData(path);
    for(int i=0;i<barang.size();i++){
      barang[i].erase(barang[i].begin() + 0);
      barang[i].erase(barang[i].begin() + 1);
    }
    if(hitungLine(path) != 0){
      cout<<"isi kategori "<<kategori<<endl;
      outBarang(barang, false, true);
      cout<<"apakah anda ingin menghapus kategori "<<
        kategori<<" beserta isinya?\n(y/n) > ";
    } else{
      cout<<"apakah anda ingin menghapus kategori "<<
        kategori<<"?\n(y/n) > ";
    }
    cin>>konf;
    if(konf == "y" || konf == "Y"){
      fs::remove_all(pathHapus);
      cout<<"kategori "<<kategori<<" berhasil dihapus!\n";
      fetchExKategori();
      cin.ignore();
      jeda();
    }
  } else {
    dataKosong();
  }
}

void listAll(){
  fetchExKategori();
  string pathBuilder;
  Array2D<string> kategori;

  if(hitungLine(pathFileKategori) != 0){
    string pilKategori;

    cout<<garis;
    pilKategori = getKategori();

    pathBuilder += pathKategori + "/" +pilKategori+ "/" + pilKategori + ".txt";
    fetchExBarang(pilKategori);
    kategori = loadData(pathBuilder);
    for(int i=0;i<kategori.size();i++){
      kategori[i].erase(kategori[i].begin());
      kategori[i].erase(kategori[i].begin() + 1);
    }
    if(hitungLine(pathBuilder) != 0){
      cout<<hapus;
      cout<<garis;
      cout<<"List barang yang tersedia di "<<pilKategori<<endl;
      cout<<garis;
      outBarang(kategori, false, true);
    } else{
      cout<<hapus;
      cout<<garis;
      cout<<"Data "<<pilKategori<<" Masih kosong\n";
      cout<<garis;
      cout<<"silahkan isi data terlebih dahulu!\n";
      cout<<garis;
    }
    cin.ignore();
    jeda();
  } 
  
  if(hitungLine(pathFileKategori) == 0 && kategori.size() == 0){
    dataKosong();
  }
  
}

void updateStock(){
  fetchExKategori();
  int id, newStock;
  char konf;
  string kategori;
  string pathUpdate;
  Array2D<string> dataBarang;
  if(hitungLine(pathFileKategori) != 0){
    kategori = getKategori();
    pathUpdate = pathKategori + "/" + kategori + "/" + kategori + ".txt";
    dataBarang = loadData(pathUpdate);
    outBarang(dataBarang, true);
    cout<<"pilih id : ";
    cin>>id;
    if(id <= 0 || id > dataBarang.size()){
      cout<<"masukkan id yang valid!"<<endl;
    } else{
      for(int i=0;i<dataBarang.size();i++){
        if(dataBarang[i][0] == to_string(id)){
          cout<<"masukkan jumlah data baru : ";
          cin>>newStock;
          cout<<"apakah anda ingin menyimpan data?\n(y/n) > "; 
          cin>>konf;
          if(konf == 'y' || konf == 'Y'){
            pathUpdate = pathKategori + "/" + kategori + "/barang/" + dataBarang[i][1] + ".txt";
            int jmlExData = hitungLine(pathUpdate);
            string idAkhir = "0";
            if(jmlExData != 0){
              ifstream bacaFile(pathUpdate);
              for(int i=0;i<jmlExData;i++){
                getline(bacaFile, idAkhir);
              }
            }
            ofstream updateFile(pathUpdate,ios::app);
            
            int totalStock = newStock+stoi(idAkhir)+1;
            for(int i=stoi(idAkhir)+1;i<totalStock;i++){
              updateFile<<i<<endl;
            }
            fetchExBarang(kategori);
            cout<<"jumlah stok berhasil diupdate!"<<endl;
          }
        }
      }
    }
    cin.ignore();
    jeda();
  }
}

void updateNama(){
  fetchExKategori();
  int id;
  string newNama;
  char konf;
  string kategori;
  string pathUpdate;
  Array2D<string> dataBarang;
  if(hitungLine(pathFileKategori) != 0){
    kategori = getKategori();
    pathUpdate = pathKategori + "/" + kategori + "/" + kategori + ".txt";
    dataBarang = loadData(pathUpdate);
    outBarang(dataBarang, true);
    cout<<"pilih id : ";
    cin>>id;
    if(id <= 0 || id > dataBarang.size()){
      cout<<"masukkan id yang valid!"<<endl;
    } else{
      for(int i=0;i<dataBarang.size();i++){
        if(dataBarang[i][0] == to_string(id)){
          cin.ignore();
          cout<<"masukkan Nama barang baru : ";
          input(newNama);
          cout<<"apakah anda ingin mengganti data?\n(y/n) > "; 
          cin>>konf;
          if(konf == 'y' || konf == 'Y'){
            string oldNamaFile = pathKategori + "/" + kategori + "/barang/" + dataBarang[i][1] + ".txt";
            string newNamaFile = pathKategori + "/" + kategori + "/barang/" + newNama + ".txt";
            dataBarang[i][1] = newNama;
            ofstream updateData(pathUpdate);
            for(int i=0;i<dataBarang.size();i++){
              updateData<<
                dataBarang[i][0]<<"|"<<
                dataBarang[i][1]<<"|"<<
                dataBarang[i][2]<<"|"<<
                dataBarang[i][3]<<"|"<<
                dataBarang[i][4]<<"|"<<
              endl;
            }

            if(rename(oldNamaFile.c_str(), newNamaFile.c_str())==0){
              cout<<"Data berhasil disimpan!"<<endl;
            } else {
              cout<<"Data gagal disimpan!"<<endl;
            }
          }
        }
      }
    }
    cin.ignore();
    jeda();
  }
}

void updateKategori(){
  fetchExKategori();
  string id, kategoriLine;
  string newKategori;
  char konf;
  string kategori;
  string pathUpdate;
  Array2D<string> dataBarang;
  if(hitungLine(pathFileKategori) != 0){
    kategori = getKategori();
    cin.ignore();
    cout<<"masukkan Nama barang baru : ";
    input(newKategori);
    cout<<"apakah anda ingin mengganti data?\n(y/n) > "; 
    cin>>konf;

    if(konf == 'y' || konf == 'Y'){
      string oldNamaKategori = pathKategori + "/" + kategori;
      string newNamaKategori = pathKategori + "/" + newKategori;
      if(rename(oldNamaKategori.c_str(), newNamaKategori.c_str())==0){
        cout<<"Data berhasil disimpan!"<<endl;
      } else {
        cout<<"Data gagal disimpan!"<<endl;
      }
      Array1D<string> dataKategori;
      string line;
      ifstream bacaKategori(pathFileKategori);
      while (getline(bacaKategori, line)){
        istringstream stream(line);
        getline(stream, id, '|');
        getline(stream, kategoriLine);
        dataKategori.push(id);
        dataKategori.push(kategoriLine);
      }
      for(int i=0;i<dataKategori.size();i++){
        if(dataKategori[i] == kategori){
          dataKategori[i] = newKategori;
        }
      }
      ofstream updateData(pathFileKategori);
      for(int i=0;i<dataKategori.size();i++){
        updateData<<
          dataKategori[i]<<"|"<<
          dataKategori[++i]<<"|"<<
        endl;
      }

    }
    cin.ignore();
    jeda();
  } else {
    cout<<"data kosong!"<<endl;
    cin.ignore();
    jeda();
  }
}









