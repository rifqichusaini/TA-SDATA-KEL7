void strukBuilder(int banyakBarang, string *namaBarang, string *totalBarang,
	string *totalHarga, int totalPembelian, string namaPelanggan, User &data){

	if(!fs::exists(pathStruk + "/" + namaPelanggan)){
		createFolder(pathStruk + "/" + namaPelanggan);

	}
	ofstream tulisLog(pathStruk + "/" + namaPelanggan + "/" + namaPelanggan + ".txt", ios::app);
	int banyakLog = hitungLine(pathStruk + "/" + namaPelanggan + "/" + namaPelanggan + ".txt");
	tulisLog<<to_string(banyakLog+1) +" - " + namaPelanggan + ".txt"<<endl;
	tulisLog.close();

	ofstream tulis(pathStruk + "/" + namaPelanggan + "/" + to_string(banyakLog+1) +" - " + namaPelanggan + ".txt");

	tulis<<"============================================"<<endl;
	tulis<<"| nama pelanggan    : "<<setw(21)<<setiosflags(ios::left)<<namaPelanggan<<"|"<<endl;
	tulis<<"| nama kasir        : "<<setw(21)<<setiosflags(ios::left)<<data.getNamaUser()<<"|"<<endl;
	tulis<<"| tanggal pembelian : "<<setw(21)<<setiosflags(ios::left)<<getTimestamp()<<"|"<<endl;
	tulis<<"============================================"<<endl;
	tulis<<"| Nama Barang        Jumlah Barang   Harga |"<<endl;
	tulis<<"============================================"<<endl;
	for (int i = 0; i < banyakBarang; i++) {
		tulis << "| " << setw(23) << setiosflags(ios::left) << namaBarang[i]
			<< setw(7) << setiosflags(ios::left) << totalBarang[i]
			<< setw(10) << setiosflags(ios::right) << totalHarga[i]
			<< " |"
			<< resetiosflags(ios::right)
			<< endl;
	}

	tulis<<"============================================"<<endl;
	tulis<<"| total pembelian   :"<<setw(21)<<setiosflags(ios::right)<<totalPembelian<<" |"<<endl;
	tulis<<"============================================"<<endl;

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

