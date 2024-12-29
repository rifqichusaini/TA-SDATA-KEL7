void strukBuilder(int banyakBarang, string *namaBarang, string *totalBarang,
	string *totalHarga, int totalPembelian, string namaPelanggan, User &data){

	if(!fs::exists(pathStruk + "/" + namaPelanggan)){
		createFolder(pathStruk + "/" + namaPelanggan);
	}
	ofstream tulisLog(pathStruk + "/" + namaPelanggan + "/" + namaPelanggan + ".txt", ios::app);
	int banyakLog = hitungLine(pathStruk + "/" + namaPelanggan + "/" + namaPelanggan + ".txt");
	tulisLog<<to_string(banyakLog+1) +" - " + namaPelanggan + ".txt"<<endl;
	tulisLog.close();

	int* hargaSatuan = new int[banyakBarang];
	for (int i = 0; i < banyakBarang; i++) {
		hargaSatuan[i] = stoi(totalHarga[i])/stoi(totalBarang[i]);
	}
	
	ofstream tulis(pathStruk + "/" + namaPelanggan + "/" + to_string(banyakLog+1) +" - " + namaPelanggan + ".txt");

	tulis<<"=============================================="<<endl;
	tulis<<"|                                            |"<<endl;
	tulis<<"|                 KONDE MART                 |"<<endl;
	tulis<<"|      Jl. Imogiri Timur KM 7.6 Grojogan     |"<<endl;
	tulis<<"|        Wirokerten BGTP Bantul DIY          |"<<endl;
	tulis<<"|                                            |"<<endl;
	tulis<<"----------------------------------------------"<<endl;
	// tulis<<"| nama pelanggan    : "<<setw(23)<<setiosflags(ios::left)<<namaPelanggan<<"|"<<endl;
	// tulis<<"| nama kasir        : "<<setw(23)<<setiosflags(ios::left)<<data.getNamaUser()<<"|"<<endl;
	// tulis<<"| tanggal pembelian : "<<setw(23)<<setiosflags(ios::left)<<getTimestamp()<<"|"<<endl;
	tulis<<namaPelanggan<<" : "<<data.getNamaUser()<<" "<<getTimestamp()<<endl;
	tulis<<"----------------------------------------------"<<endl;
	for (int i = 0; i < banyakBarang; i++) {
		// tulis << "| " << setw(23) << setiosflags(ios::left) << namaBarang[i]
		// 	<< setw(7) << setiosflags(ios::left) <<("x"+totalBarang[i])
		// 	<< setw(10) << setiosflags(ios::right) << totalHarga[i]
		// 	<< " |"
		// 	<< resetiosflags(ios::right)
		// 	<< endl;
		string harga = totalBarang[i] + "x" + to_string(hargaSatuan[i]);
		tulis << namaBarang[i]<<endl
			<< setw(30) << setiosflags(ios::left) << ("( "+totalBarang[i] + " x " + to_string(hargaSatuan[i])+" )") << "="
			<< setw(15) << setiosflags(ios::right) << totalHarga[i]
			<< resetiosflags(ios::right)
			<< endl;
	}

	tulis<<"----------------------------------------------"<<endl;
	string harga = "Rp. " + to_string(totalPembelian);
	tulis<<"| total pembelian"<<setw(27)<<setiosflags(ios::right)<<harga<<" |"<<endl;
	tulis<<"----------------------------------------------"<<endl;
	tulis<<"|                                            |"<<endl;
	tulis<<"|        MATUR NUWUN SUDAH BERBELANJA        |"<<endl;
	tulis<<"|  IG : kondemart.id, Telegram : konde mart  |"<<endl;
	tulis<<"|        Yuk NgoNDe Lagi Setiap Hari         |"<<endl;
	tulis<<"|                                            |"<<endl;
	tulis<<"=============================================="<<endl;

	tulis.close();

}

void lihatAntrian(){
	string line, nama;
	string delimiter = " - ";

	int jmlAntrian = hitungLine(pathFileAntrian);
	string *id = new string[jmlAntrian];
	string *listAntrian = new string[jmlAntrian];
	string *isiFile = new string[jmlAntrian];

	ifstream baca(pathFileAntrian);
	int i=0;
	while (getline(baca, line)){
		isiFile[i] = line;
		size_t pos = line.find(delimiter);
		if (pos != string::npos) {
			id[i] = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			listAntrian[i] = line;
		}
		i++;
	}
	baca.close();	

	cout<<hapus;
	cout<<garis;
	if(jmlAntrian != 0){
		cout<<"Urutan Antrian Pelanggan"<<endl;
		cout<<garis;
		for(int i=0;i<jmlAntrian;i++){
			cout<<i+1<<" - "<<listAntrian[i]<<endl;
		}
	} else{
		cout<<"Antrian kosong!"<<endl;
	}
	cout<<garis;

	cin.ignore();
	jeda();	
}

