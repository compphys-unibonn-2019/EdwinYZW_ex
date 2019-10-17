int myrand(){
    auto random = new TRandom(0);
    for (int i=0; i < 10; i++){
        cout << random -> Integer(10) << endl;
    }
    return 0;
}