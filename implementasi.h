void strukBuilder(int banyakBarang, string *namaBarang, string *totalBarang,
	string *totalHarga, int totalPembelian, string namaPelanggan, User &data);

// ganti Lifo
void checkoutFifo(string kategori, string barang, string jmlCheckout){
	string id;
	string pathFileBarang = pathKategori + "/" + kategori + "/barang/" + barang + ".txt" ;
	int jmlBarang = hitungLine(pathFileBarang);
	ifstream baca(pathFileBarang);

	string *isiBarang;
	int jmlBeli = stoi(jmlCheckout);
	isiBarang = new string[jmlBarang];

	if (jmlBeli > jmlBarang) {
		cout << "Error: Jumlah beli melebihi jumlah barang yang tersedia." << endl;
		delete[] isiBarang;
		return;
	}

	int i=0;
	while (getline(baca, id)) {
		isiBarang[i] = id;
		i++;
	}
	
	for (int i = 0; i < jmlBarang - jmlBeli; ++i) {
		isiBarang[i] = isiBarang[jmlBeli + i];
	}

	ofstream tulis(pathFileBarang);
	for (int i = 0; i < jmlBarang - jmlBeli; ++i) {
		tulis<<isiBarang[i]<<endl;
	}

	delete[] isiBarang;
}

void konfBarangLifo(string path, User &data){
	int banyakBarang = hitungLine(pathAntrian + "/" + path);
	string *isiBarang = new string[banyakBarang];
	string *namaBarang = new string[banyakBarang];
	string *totalBarang = new string[banyakBarang];
	string *totalHarga = new string[banyakBarang];
	ifstream baca(pathAntrian + "/" + path);
	string baris, id, kategori;
	int i=0;
	while (getline(baca, baris)){
		istringstream stream(baris);
		getline(stream, id, '|');
		getline(stream, namaBarang[i], '|');
		getline(stream, kategori, '|');
		getline(stream, totalBarang[i], '|');
		getline(stream, totalHarga[i], '|');
		isiBarang[i] = baris;
		i++;
	}
	baca.close();
    
	string namaPelanggan;
	string delimiter = " - ";

	ifstream bacaNama(pathFileAntrian);
	while (getline(bacaNama, baris)){
		size_t pos = baris.find(delimiter);
		if (pos != string::npos) {
			id = baris.substr(0, pos);
			baris.erase(0, pos + delimiter.length());

			delimiter = ".txt";
			size_t pos = baris.find(delimiter);
			if(pos != string::npos){
				namaPelanggan = baris.substr(0, pos);
			}
			break;
		}
	}
	bacaNama.close();

	int totalPembelian = 0;
	for(int i=0;i<banyakBarang;i++){
		totalPembelian += stoi(totalHarga[i]);
	}

	strukBuilder(banyakBarang, namaBarang, totalBarang, totalHarga, totalPembelian, namaPelanggan, data);

	cin.ignore();
	int counterLifo = banyakBarang;
	for (int i = banyakBarang - 1; i >= 0; i--) { 
		cout<<hapus;
		cout<<garis;
		cout<<"konfirmasi barang\n";
		cout<<garis;
		cout<<" - > Nama Barang   : "<<namaBarang[i]<<endl
			<<" - > Jumlah Barang : "<<totalBarang[i]<<endl
			<<" - > Total Harga   : "<<totalHarga[i]<<endl;
		cout<<garis;

		jeda();
		ofstream lifo(pathAntrian + "/" + path);
		for(int j=0;j<counterLifo-1;j++){
			lifo<<isiBarang[j]<<endl;
		}
		counterLifo--;
		lifo.close();
	}
	fs::remove_all(pathAntrian + "/" + path);
}

void antrianFifo(User &data){
	if(hitungLine(pathFileAntrian) != 0){
		int jmlAntrian = hitungLine(pathFileAntrian);
		string *listAntrian = new string[jmlAntrian];
		string line;
		ifstream baca(pathFileAntrian);
		int i=0;
		while(getline(baca, line)){
			listAntrian[i] = line;
			i++;
		}
		baca.close();
		konfBarangLifo(listAntrian[0], data);
		ofstream updateAntrian(pathFileAntrian);
		for(int i=1;i<jmlAntrian;i++){
			updateAntrian<<listAntrian[i]<<endl;
		}
		cout<<"antrian berhasil dilayani"<<endl;
		jeda();

	} else{
		cout<<"antrian kosong!"<<endl;
		cin.ignore();
		jeda();
	}
}


