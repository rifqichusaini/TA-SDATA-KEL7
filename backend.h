#include <algorithm>
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// #include <bits/stdc++.h> 

using namespace std;
namespace fs = std::filesystem;

#include"arrayCustom.h"
#include"control.h"
#include"output.h"
#include"masuk.h"

#include"implementasi.h"
#include"admin.h"
#include"user.h"
#include"kasir.h"

class Menu : public User{
private:
  int pilihan;
  Login L;
  Logout Out;
public:
  void menuAdmin();
  void menuUser();
  void menuKasir();

  void menu(){
    bool isInputValid = true;
    do{
      do{
        cout<<hapus;
        cout<<garis;
        cout<<"	Selamat Datang di\n"
          "Sistem Manajemen Kasir Konde Mart\n"
          "  Jl. Imogiri Timur\n";
        cout<<garis;
        if(!L.getIsLogin()){
          cout<<"1. log-in"<<endl;
          cout<<"2. sign-in"<<endl;
          cout<<"0. keluar"<<endl;
          cout<<garis;
          cout<<"masukkan pilihan anda : ";
          if(inputValidation(pilihan)){
            if(pilihan == 1){
              cout<<hapus;
              L.login();
              jeda();
            } else if(pilihan == 2){
              cout<<hapus;
              SignIn S;
              jeda();
            } else if(pilihan == 0){
              cin.ignore();
              jeda();
              cout<<hapus;
              cout<<"Bye, semoga harimu menyenangkan!"<<endl;
            } else{
              cout<<"pilihan tidak ada!"<<endl;
              cin.ignore();
              jeda();
            }
          } else{
            isInputValid = false;
            invalidInput();
          }
        } else{
          dashboard();
        }
      }while(!isInputValid);
    } while (pilihan != 0);
  }

  void dashboard(){
    if(L.getIsAdmin()){
      menuAdmin();
    } else if(L.getIsKasir()){
      if(isDbExist()){
        menuKasir();
      } else {
        cout<<"database masih kosong\nsilahkan menunggu admin mengisi barang!"<<endl;
        cout<<garis;
        Out.logout(L);
        jeda();
      }
    } else{
      if(isDbExist()){
        menuUser();
      } else {
        cout<<"database masih kosong\nsilahkan menunggu admin mengisi barang!"<<endl;
        cout<<garis;
        Out.logout(L);
        jeda();
      }
    }
  }
};

void Menu::menuAdmin(){
  int pilihan;
  bool isInputValid = true;
 
  do{ 
    cout<<hapus;
    cout<<garis;
    cout<<"selamat datang "<<L.getNamaUser()<<"!"<<endl;
    cout<<garis;
    cout<<"Menu : "<<endl;
    cout<<" 0. Logout"<<endl;
    cout<<" 1. Tambah Barang Baru"<<endl;
    cout<<" 2. Tambah Kategori Baru"<<endl;
    cout<<" 3. Hapus Barang "<<endl;
    cout<<" 4. Update Barang"<<endl;
    cout<<" 5. List Barang"<<endl;
    cout<<"masukkan pilihan : ";
    if(inputValidation(pilihan)){
      if(pilihan == 0){
        Out.logout(L);
        menu();
      } else if(pilihan == 1){
        tambahBarang();
      } else if(pilihan == 2){
        tambahKategori();
      } else if(pilihan == 4){
        cout<<"1. update stock\n";
        cout<<"2. update nama barang\n";
        cout<<"3. update nama kategori\n";
        cout<<"masukkan pilihan : ";
        if(inputValidation(pilihan)){
          if(pilihan == 1){
            updateStock();
          } else if(pilihan == 2){
            updateNama();
          } else if(pilihan == 3){
            updateKategori();
          } else{
            cout<<"pilihan tidak tersedia!\n";
            cin.ignore();
            jeda();
          }
        } else {
          isInputValid = false;
          invalidInput();
        }
      } else if(pilihan == 3){
        cout<<" 1. hapus kategori\n";
        cout<<" 2. hapus barang\n";
        cout<<"masukkan pilihan : ";
        if(inputValidation(pilihan)){
          if(pilihan == 1){
            hapusKategori();
          } else if(pilihan == 2){
            hapusBarang();
          } else{
            cout<<"pilihan tidak tersedia!\n";
            cin.ignore();
            jeda();
          }
        } else {
          isInputValid = false;
          invalidInput();
        }
      } else if(pilihan == 5){
        cout<<" 1. tampilkan per-kategori\n";
        cout<<" 2. tampilkan semua barang tersedia\n";
        cout<<"masukkan pilihan : ";
        if(inputValidation(pilihan)){
          if(pilihan == 1){
            listAll();
          } else if(pilihan == 2){
            autoListAll();
          } else{
            cout<<"pilihan tidak tersedia!\n";
            cin.ignore();
            jeda();
          }
        } else {
          isInputValid = false;
          invalidInput();
        }
      }
      else{
        cout<<"pilihan tidak tersedia!"<<endl;
        cin.ignore();
        jeda();
      }
    } else{
      isInputValid = false;
      invalidInput();
    }

  } while (!isInputValid);
}

void Menu::menuUser(){
  int pilihan;
  bool isInputValid = true;
  
  do{ 
    cout<<hapus;
    cout<<garis;
    cout<<"selamat datang "<<L.getNamaUser()<<"!"<<endl;
    cout<<garis;
    cout<<"Menu : "<<endl;
    cout<<" 0. Logout"<<endl;
    cout<<" 1. Tambah barang baru ke keranjang"<<endl;
    cout<<" 2. Hapus Barang dari keranjang"<<endl;
    cout<<" 3. Edit jumlah Barang dari keranjang"<<endl;
    cout<<" 4. lihat keranjang"<<endl;
    cout<<" 5. List Barang"<<endl;
    cout<<" 6. lihat history transaksi"<<endl;
    cout<<" 7. checkout"<<endl;
    cout<<"masukkan pilihan : ";
    if(inputValidation(pilihan)){
      if(pilihan == 0){
        Out.logout(L);
        menu();
      } else if(pilihan == 1){
        addKeranjang(L);
      } else if(pilihan == 3){
        kurangiKeranjang(L);
      } else if(pilihan == 2){
        hapusKeranjang(L);
      } else if(pilihan == 4){
        listKeranjang(L);
      } else if(pilihan == 5){
        cout<<" 1. tampilkan per-kategori\n";
        cout<<" 2. tampilkan semua barang tersedia\n";
        cout<<"masukkan pilihan : ";
        if(inputValidation(pilihan)){
          if(pilihan == 1){
            listAll();
          } else if(pilihan == 2){
            autoListAll();
          } else{
            cout<<"pilihan tidak tersedia!\n";
            cin.ignore();
            jeda();
          }
        } else {
          isInputValid = false;
          invalidInput();
        }
      } else if(pilihan == 6){
        logPesanan(L);
      } else if(pilihan == 7){
        checkout(L);
      }
      else{
        cout<<"pilihan tidak tersedia!"<<endl;
        cin.ignore();
        jeda();
      }
    } else{
      isInputValid = false;
      invalidInput();
    }

  } while (!isInputValid);
}

void Menu::menuKasir(){
  int pilihan;
  bool isInputValid = true;
  
  do{ 
    cout<<hapus;
    cout<<garis;
    cout<<"selamat datang "<<L.getNamaUser()<<"!"<<endl;
    cout<<garis;
    cout<<"Menu : "<<endl;
    cout<<" 0. Logout"<<endl;
    cout<<" 1. Lihat antrian"<<endl;
    cout<<" 2. Layani antrian"<<endl;
    cout<<"masukkan pilihan : ";
    if(inputValidation(pilihan)){
      if(pilihan == 0){
        Out.logout(L);
        menu();
      } else if(pilihan == 1){
        lihatAntrian();
      } else if(pilihan == 2){
        antrianFifo(L);
      } else{
        cout<<"pilihan tidak tersedia!"<<endl;
        cin.ignore();
        jeda();
      }
    } else{
      isInputValid = false;
      invalidInput();
    }

  } while (!isInputValid);
}

