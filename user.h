Array2D<string> fetchAllBarang(){
  Array2D<string> barangFix;
  Array2D<string> kategori;
  Array1D<string> pathBuilder;
  int line = 0;

  kategori = loadData(pathFileKategori);
  for(int i=0;i<kategori.size();i++){
    kategori[i].erase(kategori[i].begin() + 0);
  }
  for(int i=0;i<kategori.size();i++){
    string path = pathKategori + "/" + kategori[i][0] + "/" + kategori[i][0] + ".txt"; 
    pathBuilder.push_back(path);
  }
  for(int i=0;i<pathBuilder.size();i++){
    line += hitungLine(pathBuilder[i]);
  }
  for(int i=0;i<pathBuilder.size();i++){
    Array2D<string> data = loadData(pathBuilder[i]);
    // Menggunakan loop manual untuk push_back setiap elemen data ke barangFix
    for (int j = 0; j < data.size(); j++) {
      barangFix.push_back(data[j]);
    }
  }

  return barangFix;
}

void listKeranjang(User &data){
  string pathBuilder;
  pathBuilder += pathKeranjang + "/" + data.getNamaUser();
  pathBuilder += ".txt";
  if(hitungLine(pathBuilder) != 0){
    Array2D<string> isiKeranjang = loadData(pathBuilder);
    for(int i=0;i<isiKeranjang.size();i++){
      isiKeranjang[i].erase(isiKeranjang[i].begin() + 0);
    }
    outBarang(isiKeranjang);
  } else{
    cout<<"keranjang masih kosong!\nsilahkan isi data dulu\n";
  }
  cin.ignore();
  jeda();
}

void hapusKeranjang(User &data){
  int pilId;
  string konf;
  string pathFileBarang;
  string pathBuilder;
  pathBuilder += pathKeranjang + "/" + data.getNamaUser();
  pathBuilder += ".txt";
  if(hitungLine(pathBuilder) != 0){
    Array2D<string> isiKeranjang = loadData(pathBuilder);
    outBarang(isiKeranjang, true, false, false, true);
    cout<<"pilih id barang yg ingin dihapus : ";
    if(inputValidation(pilId)){
      if(pilId <= 0 || pilId > isiKeranjang.size()){
        if(pilId == 0){
          cin.ignore();
          jeda();
          return;
        } else{
          cout<<"pilih id yang valid!"<<endl;
          cin.ignore();
          jeda();
        }
      } else{
        for(int i=0;i<isiKeranjang.size();i++){
          if(to_string(pilId) == isiKeranjang[i][0]){
            cout<<"apakah anda yakin ingin menghapus "<<isiKeranjang[i][1]<<"?\n(y/n) > ";
            cin>>konf;
            if(konf == "y" || konf == "Y"){
              pathFileBarang += pathKategori + "/" + isiKeranjang[i][2] + "/barang/" + isiKeranjang[i][1] + ".txt";
              int jmlHapusBarang = stoi(isiKeranjang[i][3]);
              // ================================
              int idAwalBarang = 0;
              int stokBarang = 0;
              int jmlTotalHapusBarang = 0;
              if(hitungLine(pathFileBarang) != 0){
                stokBarang = hitungLine(pathFileBarang);
                ifstream bacaExBarang(pathFileBarang);
                string line;
                while (getline(bacaExBarang, line)){
                  idAwalBarang = stoi(line);
                  break;
                }
                
                ofstream hapusBarang(pathFileBarang);
                jmlTotalHapusBarang = jmlHapusBarang + stokBarang;
                idAwalBarang -= jmlHapusBarang;
                for(int i=0;i<jmlTotalHapusBarang;i++){
                  hapusBarang<<idAwalBarang<<endl;
                  idAwalBarang++;
                }
              } else{
                ofstream hapusBarang(pathFileBarang);
                for(int i=0;i<jmlHapusBarang;i++){
                  hapusBarang<<i+1<<endl;
                }
              }
              fetchExBarang(isiKeranjang[i][2]);
              // ==============================
              isiKeranjang.erase(isiKeranjang.begin()+i);
              for(int j=0;j<isiKeranjang.size();j++){
                isiKeranjang[j].erase(isiKeranjang[j].begin());
              }
              // ================================  
              ofstream updateKeranjang(pathBuilder);
              for(int x=0;x<isiKeranjang.size();x++){
                updateKeranjang<<x+1<<"|";
                for(int j=0;j<isiKeranjang[x].size();j++){
                  updateKeranjang<<isiKeranjang[x][j];
                  if(isiKeranjang[x].size() - 1 != j){
                    updateKeranjang<<"|";
                  }
                }
                updateKeranjang<<endl;
              }      
              // ==============================
              cout<<"Barang berhasil di hapus!"<<endl;
              cin.ignore();
              jeda();
            }
          }
        }
      }
    } else {
      invalidInput();
    }
  } else{
    cout<<"keranjang masih kosong!\nsilahkan isi data dulu\n";
    cin.ignore();
    jeda();
  }
}

void kurangiKeranjang(User &data){
  int pilId;
  string konf;
  int jmlNew;
  string pathBuilder;
  pathBuilder += pathKeranjang + "/" + data.getNamaUser();
  pathBuilder += ".txt";
  Array2D<string> dataBarang = fetchAllBarang();

  if(hitungLine(pathBuilder) != 0){
    Array2D<string> isiKeranjang = loadData(pathBuilder);
    outBarang(isiKeranjang, true, false, false, true);
    cout<<"pilih id barang yg ingin dikurangi jumlahnya : ";
    if(inputValidation(pilId)){
      if(pilId <= 0 || pilId > isiKeranjang.size()){
        if(pilId == 0){
          cin.ignore();
          jeda();
          return;
        } else{
          cout<<"pilih id yang valid!"<<endl;
          cin.ignore();
          jeda();
        }
      } else{
        cout<<hapus;
        for(int i=0;i<isiKeranjang.size();i++){
            if(to_string(pilId) == isiKeranjang[i][0]){
              Array2D<string> showStokBarang;
              Array1D<string> copyElement;
              int copyElementSize = 0;
              for(int j=0;j<dataBarang.size();j++){
                if(isiKeranjang[i][1] == dataBarang[j][1]){
                  copyElement = dataBarang[j];
                  showStokBarang.insert(showStokBarang.begin(), copyElement);
                  copyElementSize = copyElement.size();
                  for(int i=0;i<copyElementSize;i++){
                    copyElement.pop_back();
                  }
                  break;
                }
              }
              for(int i=0;i<showStokBarang.size();i++){
                showStokBarang[i].erase(showStokBarang[i].begin());
              }
              // cout<<"data stok yang tersedia di database"<<endl;
              // outBarang(showStokBarang);
              // // outBarang(showStokBarang);

              copyElement = isiKeranjang[i];
              showStokBarang.insert(showStokBarang.begin(), copyElement);
              copyElementSize = copyElement.size();
              for(int i=0;i<copyElementSize;i++){
                copyElement.pop_back();
              }
              for(int i=0;i<showStokBarang.size();i++){
                showStokBarang[i].erase(showStokBarang[i].begin());
                showStokBarang.erase(showStokBarang.begin()+1);
              }

              cout<<"data barang yang ingin dikurangi"<<endl;
              outBarang(showStokBarang, false, false, true);
              break;
            }
        }
        int j;
        for(int i=0;i<isiKeranjang.size();i++){
          if(to_string(pilId) == isiKeranjang[i][0]){
            for(j=0;j<dataBarang.size();j++){
              if(isiKeranjang[i][1] == dataBarang[j][1]){
                break;
              }
            }
            
            cout<<"masukkan jumlah baru : ";
            if(inputValidation(jmlNew)){
              if(jmlNew > stoi(isiKeranjang[i][3])){
                cout<<"jika ingin menambah barang, masuk ke menu tambah barang.\n";
                cin.ignore();
                jeda();
                break;
              } else if(jmlNew == 0 || jmlNew < 0){
                cout<<"minimal barang 1, silahkan hapus barang jika 0.\n";
                cin.ignore();
                jeda();
                break;
              } else{
                int harga;
                harga = stoi(isiKeranjang[i][4])/stoi(isiKeranjang[i][3]);
                int totalNew;
                int jmlOld = stoi(isiKeranjang[i][3]);
                isiKeranjang[i][3] = to_string(jmlNew); //------------
                totalNew = jmlNew * harga;
                isiKeranjang[i][4] = to_string(totalNew);
                for(int i=0;i<isiKeranjang.size();i++){
                  isiKeranjang[i].erase(isiKeranjang[i].begin());
                }
                cout<<hapus;
                cout<<"data baru keranjang yang telah dikurangi"<<endl;
                outBarang(isiKeranjang);
                cout<<"apakah anda yakin ingin mengganti?\n(y/n) > ";
                cin>>konf;
                if(konf == "y" || konf == "Y"){
                  // =====================================================
                  string pathFileBarang = pathKategori + "/" + isiKeranjang[i][1] + "/barang/" + isiKeranjang[i][0] + ".txt";
                  // pathBuilder = pathKeranjang + "/" + data.getNamaUser() + ".txt";
                  // ===============
                  int jmlHapusBarang = jmlOld - jmlNew;
                  // ===============
                  
                  int idAwalBarang = 0;
                  int stokBarang = 0;
                  int jmlTotalHapusBarang = 0;
                  if(hitungLine(pathFileBarang) != 0){
                    stokBarang = hitungLine(pathFileBarang);
                    ifstream bacaExBarang(pathFileBarang);
                    string line;
                    while (getline(bacaExBarang, line)){
                      idAwalBarang = stoi(line);
                      break;
                    }
                    
                    ofstream hapusBarang(pathFileBarang);
                    jmlTotalHapusBarang = jmlHapusBarang + stokBarang;
                    idAwalBarang -= jmlHapusBarang;
                    for(int i=0;i<jmlTotalHapusBarang;i++){
                      hapusBarang<<idAwalBarang<<endl;
                      idAwalBarang++;
                    }
                  } else{
                    ofstream hapusBarang(pathFileBarang);
                    for(int i=0;i<jmlHapusBarang;i++){
                      hapusBarang<<i+1<<endl;
                    }
                  }
                  fetchExBarang(isiKeranjang[i][1]);

                  // isiKeranjang.erase(isiKeranjang.begin()+i);
                  // for(int j=0;j<isiKeranjang.size();j++){
                  //   isiKeranjang[j].erase(isiKeranjang[j].begin());
                  // }

                  // ofstream updateKeranjang(pathBuilder);
                  // for(int x=0;x<isiKeranjang.size();x++){
                  //   updateKeranjang<<x+1<<"|";
                  //   for(int j=0;j<isiKeranjang[x].size();j++){
                  //     updateKeranjang<<isiKeranjang[x][j];
                  //     if(isiKeranjang[x].size() - 1 != j){
                  //       updateKeranjang<<"|";
                  //     }
                  //   }
                  //   updateKeranjang<<endl;
                  // }      
                  // =====================================================
                  ofstream updateKeranjang(pathBuilder);

                  for(int i=0;i<isiKeranjang.size();i++){
                    updateKeranjang<<i+1<<"|";
                    for(int j=0;j<isiKeranjang[i].size(); j++){
                      updateKeranjang<<isiKeranjang[i][j]<<"|";
                    }
                    updateKeranjang<<endl;
                  }
                }
              }
            } else{
              invalidInput();
            }
          }
        }
      }
    } else {
      invalidInput();
    }
  } else{
    cout<<"keranjang masih kosong!\nsilahkan isi data dulu\n";
    cin.ignore();
    jeda();
  }
}

void addKeranjang(User &data){
  int id;
  int jml;
  string pilKategori;
  string pilihan;
  bool pilValid = true;
  string pathBuilder;
  pathBuilder += pathKeranjang + "/" + data.getNamaUser();
  pathBuilder += ".txt";

  string path;
  Array2D<string> barangPilihan;
  Array2D<string> oldData;
  Array2D<string> dataBarang;
  Array2D<string> barangFix;
  bool isOld = true;
  int line = 0;

  do{
    pilKategori = getKategori();
    barangFix = fetchAllBarang();
    path = pathKategori + "/" + pilKategori + "/" + pilKategori + ".txt";
    if(hitungLine(path) != 0){
      dataBarang = loadData(path);
      // for(int i=0;i<dataBarang.size();i++){
      //   dataBarang[i].erase(dataBarang[i].begin());
      // }
      cout<<hapus;
      cout<<garis;
      if(isOld){
        oldData = loadData(pathBuilder);
        for(int i=0;i<oldData.size();i++){
          oldData[i].erase(oldData[i].begin());
        }
        isOld = false;
      }
      if(hitungLine(pathBuilder) != 0 && barangPilihan.size() == 0){
        barangPilihan = loadData(pathBuilder);
        for(int i=0;i<barangPilihan.size();i++){
          barangPilihan[i].erase(barangPilihan[i].begin());
        }
      }
      if(barangPilihan.size() != 0){
        cout<<"barang yg sudah diinput"<<endl;
        cout<<garis;
        outBarang(barangPilihan, false, false);
        cout<<garis;
      }
      cout<<"data pada kategori "<<pilKategori<<endl;
      cout<<garis;
      outBarang(dataBarang, true, false, false, false, true);
      cout<<"masukkan id barang yang ingin dipilih : ";
      if(inputValidation(id)){
        if(id <= 0 || id > hitungLine(path)){
          if(id == 0){
            cin.ignore();
            jeda();
            pilihan = "y";
          } else{
            cout<<"pilihan tidak ada"<<endl;
            cin.ignore();
            jeda();
          }
          pilihan = "y";
        } else{
          bool isNew = true;
          for(int i=0;i<barangFix.size();i++){
            if(to_string(id) == barangFix[i][0] && pilKategori == barangFix[i][2]){
              for(int j=0;j<barangPilihan.size();j++){
                if(barangPilihan[j][0] == barangFix[i][1]){
                  isNew = false;
                }
              }
              if(stoi(barangFix[i][3]) <= 0){
                cout<<"barang sudah habis!\n";
                cin.ignore();
                jeda();
                break;
              } else{
                if(!isNew){
                  for(int j=0;j<barangPilihan.size();j++){
                    if(barangPilihan[j][0] == barangFix[i][1]){
                      if("0" != barangFix[i][3]){
                        cout<<"masukkan jumlah "<<barangFix[i][1]<<" yg ingin dibeli : ";
                        if(inputValidation(jml)){
                          // int jmlTmp = stoi(barangPilihan[j][2]);
                          // jmlTmp += jml;
                          if(jml > stoi(barangFix[i][3])){
                            cout<<"anda memasukkan barang lebih dari stok!\n";
                            cin.ignore();
                            jeda();
                          } else if(jml <= 0 ){
                            cout<<"anda memasukkan barang kurang dari atau sama dengan 0!\n";
                            cin.ignore();
                            jeda();
                          } else{
                            int jmlTmp = stoi(barangPilihan[j][2]);
                            jmlTmp += jml;
                            int totalHarga;
                            totalHarga = jmlTmp * stoi(barangFix[i][4]);
                            barangPilihan[j][2] = to_string(jmlTmp);
                            barangPilihan[j][3] = to_string(totalHarga);
                          
                            barangFix[i][3] = to_string(jmlTmp);
                            // =========================================
                            for(int j=0;j<dataBarang.size();j++){
                              if(dataBarang[j][1] == barangFix[i][1]){
                                int jmlFinal = stoi(dataBarang[j][3]);
                                jmlFinal -= jml;
                                dataBarang[j][3] = to_string(jmlFinal);
                                barangFix[j][1] = to_string(jmlFinal);
                                break;
                              }
                            }
                            ofstream updateBarang(path);
                            for(int j=0;j<dataBarang.size();j++){
                              for(int k=0;k<dataBarang[j].size();k++){
                                updateBarang<<dataBarang[j][k];
                                if(dataBarang[j].size() - 1 != k){
                                  updateBarang<<"|";
                                }
                              }
                              updateBarang<<endl;
                            }
                            // =========================================
                          }
                        } else{
                          invalidInput();
                        }
                      } else{
                        cout<<"anda sudah memasukkan semua barang!"<<endl;
                      }
                      break;
                    } 
                  }
                } else{
                  cout<<"masukkan jumlah "<<barangFix[i][1]<<" yg ingin dibeli : ";
                  if(inputValidation(jml)){
                    if(jml > stoi(barangFix[i][3])){
                      cout<<"anda memasukkan barang lebih dari stok!\n";
                      cin.ignore();
                      jeda();
                    } else if(jml <= 0){
                      cout<<"anda memasukkan barang kurang dari atau sama dengan 0!\n";
                      cin.ignore();
                      jeda();
                    } else{
                      Array1D<string> barangTmp;
                      int totalHarga;
                      barangTmp.push_back(barangFix[i][1]);
                      barangTmp.push_back(barangFix[i][2]);
                      barangTmp.push_back(to_string(jml));
                      totalHarga = jml * stoi(barangFix[i][4]);
                      barangTmp.push_back(to_string(totalHarga));
                      barangPilihan.push_back(barangTmp);
                      // =======================
                      for(int j=0;j<dataBarang.size();j++){
                        if(dataBarang[j][1] == barangFix[i][1]){
                          int jmlFinal = stoi(dataBarang[j][3]);
                          jmlFinal -= jml;
                          dataBarang[j][3] = to_string(jmlFinal);
                          barangFix[j][1] = to_string(jmlFinal);
                          break;
                        }
                      }
                      ofstream updateBarang(path);
                      for(int j=0;j<dataBarang.size();j++){
                        for(int k=0;k<dataBarang[j].size();k++){
                          updateBarang<<dataBarang[j][k];
                          if(dataBarang[j].size() - 1 != k){
                            updateBarang<<"|";
                          }
                        }
                        updateBarang<<endl;
                      }
                      // =======================
                    }
                  } else{
                    invalidInput();
                  }
                }
                break;
              }
            }
          }
          cout<<"apakah anda ingin menambah data?\n(y/n) > ";
          cin>>pilihan;
        } 
      } else{
        invalidInput();
        pilihan = "y";
      }
    } else if(pilKategori == ""){
      return;
    } else{
      dataKosong();
      pilihan = "y";
      // return;
    }
  } while (pilihan == "Y" || pilihan == "y");

    if(barangPilihan.size() != 0){
      bool isSave;
      do {  
        isSave = true;
        cout<<hapus;
        cout<<garis;
        cout<<"barang yg sudah diinput"<<endl;
        cout<<garis;
        outBarang(barangPilihan, false, false);
        cout<<garis;

        cout<<"apakah anda ingin menyimpan ke keranjang?\n(y/n) > ";
        cin>>pilihan;
        if(pilihan == "Y" || pilihan == "y"){
          // {}
          ofstream tulis(pathKeranjang + "/" + data.getNamaUser() + ".txt");
          for(int i=0;i<barangPilihan.size();i++){
            bool isUpdated = false;
            // ===================================
            for(int j=0;j<oldData.size();j++){
              if(oldData[j][0] == barangPilihan[i][0] && oldData[j][1] == barangPilihan[i][1]){
                if(oldData[j][2] != barangPilihan[i][2]){
                  isUpdated = true;
                  int jmlUpdate = stoi(barangPilihan[i][2]);
                  jmlUpdate -= stoi(oldData[j][2]);
                  checkoutFifo(barangPilihan[i][1], barangPilihan[i][0], to_string(jmlUpdate));
                  break;
                }
              } 
            }
            if(!isUpdated){
              checkoutFifo(barangPilihan[i][1], barangPilihan[i][0], barangPilihan[i][2]);
            }
            // ===================================
            tulis<<i+1<<"|";
            for(int j=0;j<barangPilihan[i].size(); j++){
              tulis<<barangPilihan[i][j];
              if(barangPilihan[i].size() - 1 != j){
                tulis<<"|";
              }
            }
            tulis<<endl;
          }
          
        } else{
          cout<<"apakah anda yakin tidak ingin menyimpan?\ndata tidak bisa dikembalikan!\n(y/n) > ";
          cin>>pilihan;
          if(pilihan == "Y" || pilihan == "y"){

            // gapenting
            // =========================
            // for(int i = 0;i<barangPilihan.size();i++){
            //   for(int j=0;j<barangFix.size();j++){
            //     if(barangPilihan[i][0] == barangFix[j][1]){
            //       int jmlTmp = stoi(barangPilihan[i][2]);
            //       jmlTmp += stoi(barangFix[j][3]);
            //       barangFix[j][3] = to_string(jmlTmp);
            //     }
            //   }
            // }
            // =========================
            
            // otomatis
            Array1D<string> kategori = bacaFolder(pathKategori);
            for(int i=0;i<kategori.size();i++){
              fetchExBarang(kategori[i]);
            }
            isSave = true;
          }else{
            isSave = false;
          }
        }
      } while (!isSave);
    } else {
      cout<<"belum ada barang yang dipilih!\n";
    }
    jeda();
}

void checkout(User &data){
	string pathFileKeranjang = pathKeranjang + "/" + data.getNamaUser() + ".txt";
  string pathFileBarang;
  // bool isValidCheckout = true;
  bool isPriority;

  if(hitungLine(pathFileKeranjang) != 0){
    cout<<"apakah anda berkebutuhan khusus?\n(1 : ya | 0 : tidak) : ";
    cin>>isPriority;
    Array2D<string> keranjang = loadData(pathFileKeranjang);
    Array2D<string> allBarang;
    

    // for(int i=0;i<keranjang.size();i++){
    //   pathFileKeranjang = pathKategori+"/"+keranjang[i][2]+"/"+keranjang[i][2]+".txt";
    //   allBarang = loadData(pathFileKeranjang);
    //   for(int j=0;j<allBarang.size();j++){
    //     if(keranjang[i][1] == allBarang[j][1] && keranjang[i][2] == allBarang[j][2]){
    //       int jmlBaru = stoi(allBarang[j][3]);
    //       jmlBaru -= stoi(keranjang[i][3]);
    //       allBarang[j][3] = to_string(jmlBaru);
    //       if(stoi(allBarang[j][3]) < 0){
    //         isValidCheckout = false;
    //       }
    //       break;
    //     }
    //   }
    // }
    
    // if(isValidCheckout){
      Array1D<string> listAntrian;
      Array1D<string> listAntrianPriority;
      Array2D<string> listId;
      Array2D<string> listIdPriority;

      int jmlAntrian = 0;
      int jmlAntrianPriority = 0;

      if(hitungLine(pathFileAntrian) != 0){
        string line;
        string id;
        string delimiter = " - ";
        string delimiterPriority = "P - ";

        ifstream bacaPriority(pathFileAntrian);
        while (getline(bacaPriority, line)){
          size_t pos = line.find(delimiterPriority);
          if (pos != string::npos) {
            id = line.substr(0, pos);
            line.erase(0, pos + delimiterPriority.length());
            listAntrianPriority.push_back(id);
            listAntrianPriority.push_back(line);
            listIdPriority.push_back(listAntrianPriority);
            listAntrianPriority.pop_back();
            listAntrianPriority.pop_back();
          }
        }
        ifstream baca(pathFileAntrian);
        while (getline(baca, line)){
          size_t pos = line.find(delimiter);
          if (pos != string::npos) {
            id = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            listAntrian.push_back(id);
            listAntrian.push_back(line);
            listId.push_back(listAntrian);
            listAntrian.pop_back();
            listAntrian.pop_back();
            jmlAntrian++;
          }
        }
      }
      string pathFileAntrianUser = pathKeranjang + "/" + data.getNamaUser() + ".txt";
      string pathFileAntrianNew;
      // =============== fifo priority ==============
      if(isPriority){
        // mendapatkan nilai akhir
        if(listIdPriority.size() != 0){
          jmlAntrianPriority = stoi(listIdPriority[listIdPriority.size()-1][0]);
        }

        for(int i=0;i<listIdPriority.size();i++){
          listId.erase(listId.begin());
        }
        pathFileAntrianNew = pathAntrian + "/" + to_string(jmlAntrianPriority + 1) + "P - " +data.getNamaUser() + ".txt";

        ofstream tulis1(pathFileAntrian);
        for(int i=0;i<listIdPriority.size();i++){
          tulis1<<listIdPriority[i][0]<<"P - "<<listIdPriority[i][1]<<endl;
        }
        tulis1.close();
        
        ofstream tulisNew(pathFileAntrian, ios::app);
        tulisNew<<to_string(jmlAntrianPriority + 1) + "P - " +data.getNamaUser() + ".txt"<<endl;

        ofstream tulis2(pathFileAntrian, ios::app);
        int j = jmlAntrianPriority;
        j+=2;
        for(int i=0;i<listId.size();i++){
          tulis2<<j<<" - "<<listId[i][1]<<endl;
          j++;
        }
        tulis2.close();

        for(int i=listId.size()-1;i>=0;i--){
          string oldQueue = pathAntrian + "/" + listId[i][0] + " - " + listId[i][1]; 
          string newQueue = pathAntrian + "/" + to_string(j-1) + " - " + listId[i][1];
          rename(oldQueue.c_str(), newQueue.c_str());
          j--;
        }
      // ============================================
      } else{
        int antrianAkhir;
        if(listId.size()!=0){
          antrianAkhir = stoi(listId[listId.size()-1][0]);
        } else{
          antrianAkhir = 0;
        }

        ofstream tulis(pathFileAntrian);
        pathFileAntrianNew = pathAntrian + "/" + to_string(antrianAkhir + 1) + " - " +data.getNamaUser() + ".txt";
        for(int i=0;i<listId.size();i++){
          tulis<<listId[i][0]<<" - "<<listId[i][1]<<endl;
        }
        tulis.close();
        ofstream tulisNew(pathFileAntrian, ios::app);
        tulisNew<<to_string(antrianAkhir + 1) + " - " +data.getNamaUser() + ".txt"<<endl;
      }

      fs::copy(pathFileAntrianUser, pathFileAntrianNew);
      remove(pathFileAntrianUser.c_str());

// ga dipake
// ===============================
      // ofstream update(pathFileKeranjang);
      // for(int i=0;i<allBarang.size();i++){
      //   for(int j=0;j<allBarang[i].size();j++){
      //     update<<allBarang[i][j];
      //     if(allBarang[i].size() - 1 != j){
      //       update<<"|";
      //     }
      //   }
      //   update<<endl;
      // }
// ===============================

// percobaan
      // for(int i=0;i<keranjang.size();i++){
      //   checkoutFifo(keranjang[i][2], keranjang[i][1], keranjang[i][3]);
      // }
      
      Array1D<string> kategori = bacaFolder(pathKategori);
      for(int i=0;i<kategori.size();i++){
        fetchExBarang(kategori[i]);
      }
      
      cout<<"Barang berhasil di checkout!"<<endl;
      cin.ignore();
      jeda();
    // } else{
    //   cout<<"ada barang yang sudah habis silahkan edit keranjang!\n";
    //   cin.ignore();
    //   jeda();
    // }

  } else{
    cout<<"keranjang masih kosong!\nsilahkan mengisi keranjang terlebih dahulu\n";
    cin.ignore();
    jeda();
  }  
}

bool isDbExist(){
  Array1D<string> kategori = bacaFolder(pathKategori);
  return kategori.size() > 0 ? true : false;
}

void logPesanan(User &data){
  string namaUser = data.getNamaUser();

  if(fs::exists(pathStruk + "/" + namaUser)){
    string path = pathStruk + "/" + namaUser + "/" + namaUser + ".txt";
    int banyakLog = hitungLine(path);
    string *isiFile = new string[banyakLog];
    int pilihan;
    string baris;

    cout<<hapus;
    cout<<garis;
    cout<<"List history transaksi"<<endl;
    cout<<garis;
    for(int i=0;i<banyakLog;i++){
      cout<<" -> History transaksi ke-"<<i+1<<endl;
    }
    cout<<garis;
    cout<<"lihat history ke : ";
    cin>>pilihan;

    ifstream bacaLog(path);
    int i=0;
    while (getline(bacaLog, baris)){
      isiFile[i] = baris;
      i++;
    }
    
    cout<<hapus;
    cout<<garis;
    cout<<"history pembelian ke "<<pilihan<<endl;
    cout<<garis<<endl;
    ifstream bacaStruk(pathStruk + "/" + namaUser + "/" + isiFile[pilihan-1]);
    while (getline(bacaStruk, baris)){
      cout<<baris<<endl;
    }
  } else {
    cout<<"belum ada history transaksi!"<<endl;
  }
    cin.ignore();
    jeda();
  
}

