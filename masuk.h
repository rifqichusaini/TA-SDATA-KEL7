class User {
protected:
  bool isAdmin = false, isLogin = false, isKasir = false;
  string user;
  string namaUser;
  string pathCekCreds = pathCredentials+"/account.txt";
public:
  void setUser(bool isAdmin, bool isLogin, bool isKasir, string username, string nama) {
    this->isAdmin = isAdmin;
    this->isLogin = isLogin;
    this->isKasir = isKasir;
    this->user = username;
    this->namaUser = nama;
  }
  bool getIsAdmin() { return isAdmin; }
  bool getIsLogin() { return isLogin; }
  bool getIsKasir() { return isKasir; }
  string getUser() { return user; }
  string getNamaUser() { return namaUser; }
};

class Login : public User{
private:
  string user, pass;
public:
  void login(){
    cout << garis;
    cout << "Selamat datang kembali!" << endl;
    cout << garis;
    cin.ignore();
    cout << "Masukkan username: ";
    getline(cin, user);

    cout << "Masukkan password: ";
    getline(cin, pass);
    cout << garis;
    
    if (isLoginValid()) {
      cout << "Login berhasil!" << endl;
    } else {
      cout<< "User tidak dikenali!\n"
        << "Silahkan cek kembali username\n"
        << "dan password Anda\n"
        << "atau silahkan daftar akun!"
      << endl;
    }
    cout << garis;
  }

  bool isLoginValid() {
    
    ifstream file(pathCekCreds);
    string userCek, passCek, line, namaUser;

    if (file.is_open()) {
      while (getline(file, line)) {
        istringstream stream(line);

        getline(stream, userCek, '|');
        getline(stream, passCek, '|');
        getline(stream, namaUser);

        size_t pos = userCek.find("kasir");
        if (pos != string::npos) {
          userCek = userCek.substr(pos, 5);
        }

        if ("admin" == this->user && "pass" == this->pass) {
          setUser(true, true, false,  this->user, namaUser);
          return true;
        } else if(userCek == "kasir " && passCek == this->pass){
          setUser(false, true, true,  this->user, namaUser);
          return true;
        }  else if (userCek == this->user && passCek == this->pass) {
          setUser(false, true, false,  this->user, namaUser);
          return true;
        }
      }
      file.close();
    }
    return false;
  }
};

class SignIn : public User{
private:
  string user, pass, namaUser;
public:

  SignIn(){
    cout<<garis;
    cout<<"selamat datang pengguna baru!"<<endl;
    cout<<"silahkan membuat akun baru"<<endl;
    cout<<garis;
    cin.ignore();
    cout<<"masukkan nama lengkap anda sesuai ktp : ";
    getline(cin, namaUser);
    if(isNamaValid()){
      cout<<"masukkan username : ";
      getline(cin, user);
      
      if(isNamaValid() && isUsrValid()){
        cout<<"masukkan password : ";
        getline(cin, pass);
        cout<<garis;
        cout<<"akun berhasil didaftarkan!\nsilahkan login"<<endl;
        cout<<garis;
        tambahUser();
        
      }
    }
  }
  void tambahUser(){
    ofstream out(pathCekCreds, ios::app);
    out<<user<<"|"<<pass<<"|"<<namaUser<<endl;
    out.close();
  }

  bool isUsrValid(){
    ifstream file(pathCekCreds);
    string userCek, passCek, namaCek, line;

    while (getline(file, line)) {
      istringstream stream(line);

      getline(stream, userCek, '|');
      getline(stream, passCek, '|');
      getline(stream, namaCek);

      if(userCek == this->user){
        cout<<garis;
        cout<<"username sudah tersedia,"
          "\nsilahkan isi username yang berbeda"<<endl;
        cout<<garis;
        return false;
      }
    }
    file.close();
    
    return true;
  }
  bool isNamaValid(){
    ifstream file(pathCekCreds);
    string userCek, passCek, namaCek, line;

    while (getline(file, line)) {
      istringstream stream(line);

      getline(stream, userCek, '|');
      getline(stream, passCek, '|');
      getline(stream, namaCek);

      if(namaCek == this->namaUser){
        cout<<garis;
        cout<<"nama sudah terdaftar di database,"
          "\nsilahkan login jika anda sudah terdaftar"<<endl;
        cout<<garis;
        return false;
      }
    }
    file.close();
    
    return true;
  }
};

class Logout : public User{
public:
  void logout(Login &L){
    L.setUser(false, false, false, L.getUser(), L.getNamaUser());
  }
};
