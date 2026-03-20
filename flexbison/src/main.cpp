int main(int ac, char**av)
{
  FlexParser fp();
 
  aspen::Builder bldr;
  IsaEditor iedit(&bldr,&qtapp);
  AspenGui  gui(ac,av,&iedit);

  iedit.machineName = "CP"; //FIXME
  gui.setWindowIcon(QPixmap(":/icons/aspenicon.png"));
  gui.show();
//  splash.finish(&gui);

  return qtapp.exec();
}
