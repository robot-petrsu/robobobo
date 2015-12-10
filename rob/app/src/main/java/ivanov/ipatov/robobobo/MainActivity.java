package ivanov.ipatov.robobobo;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.UUID;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.bluetooth.*;
import android.content.Intent;

public class MainActivity extends Activity {
    private static final int REQUEST_ENABLE_BT = 1;
    final int ArduinoData = 1;        
    final String LOG_TAG = "myLogs";
    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private static String MacAddress = "98:D3:31:B0:81:7F";
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private ConnectedThred MyThred = null;
    public TextView Speed_inf, mytext, cBack;
    Button b_up, b_down, b_left, b_right, up_speed, down_speed;
    Button signal;
    Button autopilot;
    byte autop = 0;;
    byte sign = 0;
    byte ind_up = 0;
    byte ind_down = 0;
    byte ind_left = 0;
    byte ind_right = 0;
    int speed = 10;
    String spd = "1";
    Handler h;
    String s;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
                
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        mytext = (TextView) findViewById(R.id.textView1);
        
        if (btAdapter != null){
        	if (btAdapter.isEnabled()){
        //		mytext.setText("Bluetooth включен.");
        	}else
        	{
        		Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
        		startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        	}
        	
        }else
        {
        	//MyError("Fatal Error", "Bluetooth ОТСУТСТВУЕТ");
        }

        Speed_inf = (TextView) findViewById(R.id.textView3);
        
        signal = (Button) findViewById(R.id.toggleButton1);
        autopilot = (Button) findViewById(R.id.toggleButton2);
        
        b_up = (Button) findViewById(R.id.button1);
        b_down = (Button) findViewById(R.id.button2);
        b_left = (Button) findViewById(R.id.button3);
        b_right = (Button) findViewById(R.id.button4);
        up_speed = (Button) findViewById(R.id.button5);
        down_speed = (Button) findViewById(R.id.button6);
        
        up_speed.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(speed < 10){
            		speed = speed + 1;
            		MyThred.sendData(7); //100 - увеличение скорости
            		spd = String.valueOf(speed);
            		Speed_inf.setText(spd);
            	}
            }            
        });
        
        signal.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(sign == 0){
            		MyThred.sendData(5); //воспроизвести
            		sign = 1;
            	}
            	else{
            		MyThred.sendData(6); //заглушить
            		sign = 0;
            	}
            }
        });
        
        autopilot.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(autop == 0){
            		MyThred.sendData(9); 
            		autop = 1;
            	}
            	else{
            		MyThred.sendData(9);
            		autop = 0;
            	}
            }
        });
        
        down_speed.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            	if(speed > 0){
            		speed = speed - 1;
            		MyThred.sendData(8); //99 - уменьшение скорости
            		spd = String.valueOf(speed);
            		Speed_inf.setText(spd);
            	}
            }            
        });
        b_up.setOnClickListener(new OnClickListener() {
          public void onClick(View v) {
           s = "";
           if(ind_up == 0){
           MyThred.sendData(1);
           mytext.setText("Вперед");
           ind_up = 1;
           ind_down = 0;
           ind_left = 0;
           ind_right = 0;
           } 
           else{          
        	   MyThred.sendData(0);
               mytext.setText("СТОП");
               ind_up = 0;       	   
            }
          }
        });
      
        b_down.setOnClickListener(new OnClickListener() {
          public void onClick(View v) {
           s = "";  
           if(ind_down == 0){
               MyThred.sendData(2);
               mytext.setText("Назад");
               ind_up = 0;
               ind_down = 1;
               ind_left = 0;
               ind_right = 0;
               } 
               else{          
            	   MyThred.sendData(0);
                   mytext.setText("СТОП");
                   ind_down = 0;       	   
                }

          }
        });
        
        b_left.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
             s = "";
             if(ind_left == 0){
                 MyThred.sendData(4);
                 mytext.setText("Налево");
                 ind_up = 0;
                 ind_down = 0;
                 ind_left = 1;
                 ind_right = 0;
                 } 
                 else{          
              	   MyThred.sendData(0);
                     mytext.setText("СТОП");
                     ind_left = 0;       	   
                  }
            }
          });


        b_right.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
            s = ""; 
            if(ind_right == 0){
                MyThred.sendData(3);
                mytext.setText("Направо");
                ind_up = 0;
                ind_down = 0;
                ind_left = 0;
                ind_right = 1;
                } 
                else{          
             	   MyThred.sendData(0);
                    mytext.setText("СТОП");
                    ind_right = 0;       	   
                 }       
            }
          });
        
        
        
        h = new Handler() {
            public void handleMessage(android.os.Message msg) {
              switch (msg.what) {
              case ArduinoData:
            	  byte[] readBuf = (byte[]) msg.obj;
                  String strIncom = new String(readBuf, 0, msg.arg1);
                  Log.d(LOG_TAG, "***Получили строку***"+ strIncom);
                  s = s + strIncom;
            	  cBack.setText(s);
                  break;
              }
            };
          };
        
    }
    
    @Override
    public void onResume() {
        super.onResume();
      
        BluetoothDevice device = btAdapter.getRemoteDevice(MacAddress);
        Log.d(LOG_TAG, "***Получили удаленный Device***"+device.getName());
          
        try {
            btSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
            Log.d(LOG_TAG, "...Создали сокет...");
          } catch (IOException e) {
            MyError("Fatal Error", "В onResume() Не могу создать сокет: " + e.getMessage() + ".");
          }	 
        
        btAdapter.cancelDiscovery();	    
        Log.d(LOG_TAG, "***Отменили поиск других устройств***");
        
        Log.d(LOG_TAG, "***Соединяемся...***");
        try {
          btSocket.connect();
          Log.d(LOG_TAG, "***Соединение успешно установлено***");
          mytext.setText("Bluetooth включен. Робот подключен");
        } catch (IOException e) {
          try {
            btSocket.close();
          } catch (IOException e2) {
            MyError("Fatal Error", "В onResume() не могу закрыть сокет" + e2.getMessage() + ".");
          }
        }
       	  
        MyThred = new ConnectedThred(btSocket);	    
        MyThred.start();
      }
    
      @Override
      public void onPause() {
        super.onPause();
      
        Log.d(LOG_TAG, "...In onPause()...");
      
        if (MyThred.status_OutStrem() != null) {
            MyThred.cancel();
        }
      
        try     {
          btSocket.close();
        } catch (IOException e2) {
        	MyError("Fatal Error", "В onPause() Не могу закрыть сокет" + e2.getMessage() + ".");
        }
      }	
    
    private void MyError(String title, String message){
            Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
            finish();
    }

      
     //для приема/передачи данных  
     private class ConnectedThred extends Thread{
         private final BluetoothSocket copyBtSocket;
         private final OutputStream OutStrem;
         private final InputStream InStrem;
         
         public ConnectedThred(BluetoothSocket socket){
             copyBtSocket = socket;
             OutputStream tmpOut = null;
             InputStream tmpIn = null;
             try{
                 tmpOut = socket.getOutputStream();
                 tmpIn = socket.getInputStream();
             } catch (IOException e){}
             
             OutStrem = tmpOut;
             InStrem = tmpIn;
         }
         
         public void run()
         {
             byte[] buffer = new byte[512];
             int bytes;
             
             while(true){
                 try{
                     bytes = InStrem.read(buffer);
                     h.obtainMessage(ArduinoData, bytes, -1, buffer).sendToTarget();
                 }catch(IOException e){break;} 
                 
             } 
             
         }
         
         public void sendData(int i) {
                //byte[] msgBuffer = message;
                Log.d(LOG_TAG, "***Отправляем данные: " + i + "***");
              
                try {
                	OutStrem.write(i);
                } catch (IOException e) {}
        }
         
         public void cancel(){
             try {
                 copyBtSocket.close();
             }catch(IOException e){}			 
         }
         
         public Object status_OutStrem(){
             if (OutStrem == null){return null;		
             }else{return OutStrem;}
         }
     } 
}