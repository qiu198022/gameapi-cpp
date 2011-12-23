package playtomic.cpp;

import playtomic.cpp.R;



import playtomic.cpp.L;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import java.util.Timer;
import java.util.TimerTask;


public class PlaytomicActivity extends Activity {
	
	String logBuffer = "";
	private static final long ONE_MINUTE = 1000;
	private static final long THIRTY_SECONDS = 1000;

	private TimerTask mPingTask;
	private final Handler mHandler = new Handler();
	private Timer mT;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        initCpp();
		EditText log = (EditText) findViewById(R.id.txLog);
		InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(log.getWindowToken(), 0);		
		
		// first ping 1 minute, then 30 seconds
	    //
	    startTimer(ONE_MINUTE, THIRTY_SECONDS);
	    
		Button button;
			
		button = (Button) findViewById(R.id.cmdLogPlay);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_logPlay();
			}
		});

		button = (Button) findViewById(R.id.cmdLogCustomMetric);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_logCustomMetric();
			}
		});


		button = (Button) findViewById(R.id.cmdLogLevelCounterMetric);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_logLevelCounterMetric();
			}
		});

		button = (Button) findViewById(R.id.cmdLogLevelAverageMetric);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_logLevelAverageMetric();
			}
		});

		button = (Button) findViewById(R.id.cmdLogLevelRangedMetric);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_logLevelRangedMetric();
			}
		});

		button = (Button) findViewById(R.id.cmdLoadGameVars);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_loadGameVars();
			}
		});

		button = (Button) findViewById(R.id.cmdGeoIP);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_geoip();
			}
		});

		button = (Button) findViewById(R.id.cmdLeaderboardList);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_leaderBoardList();
			}
		});

		button = (Button) findViewById(R.id.cmdLeaderboardSave);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_leaderboardSave();
			}
		});

		button = (Button) findViewById(R.id.cmdLeaderboardSaveAndList);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_leaderboardSaveAndList();
			}
		});
		
		button = (Button) findViewById(R.id.cmdLevelList);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_levelList();
			}
		});

		button = (Button) findViewById(R.id.cmdLevelLoad);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_levelLoad();
			}
		});

		button = (Button) findViewById(R.id.cmdLevelRate);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_levelRate();
			}
		});
		
		button = (Button) findViewById(R.id.cmdLevelSave);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_levelSave();
			}
		});

		button = (Button) findViewById(R.id.cmdLoadPlays);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_loadPlays();
			}
		});

		button = (Button) findViewById(R.id.cmdLoadPlaytime);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_loadPlaytime();
			}
		});

		button = (Button) findViewById(R.id.cmdLoadViews);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_loadViews();
			}
		});
		
		button = (Button) findViewById(R.id.cmdFreeze);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_Freeze();
			}
		});

		button = (Button) findViewById(R.id.cmdUnFreeze);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View view) {
				_UnFreeze();
			}
		});
    }
    @Override
    public void onPause()
    {
    	super.onPause();
    	Freeze();
    }
    @Override
    public void onResume()
    {
    	super.onResume();
    	UnFreeze();
    }
    
    @Override
    public void onDestroy()
    {
    	super.onDestroy();
    	Destroy();
    }
   
    private native void initCpp();
    
    private void _logPlay() {
    	logPlay();
    }
    private native void logPlay();
    
    private void _logCustomMetric() {
    	logCustomMetric();
    }
	private native void logCustomMetric();

	private void _logLevelAverageMetric() {
		logLevelAverageMetric();
	}
	private native void logLevelAverageMetric();

	private void _logLevelCounterMetric() {
		logLevelCounterMetric();
	}
	private native void logLevelCounterMetric();
	
	private void _logLevelRangedMetric() {
		logLevelRangedMetric();
	}
	private native void logLevelRangedMetric();
	
	private void _loadGameVars() {
		loadGameVars();
	}
	private native void loadGameVars();

	private void _geoip() {
		geoip();
	}
	private native void geoip();	
	
	private void _leaderboardSave() {
		leaderboardSave();
	}
	private native void leaderboardSave();

	private void _leaderBoardList() {
		leaderboardList();
	}
	private native void leaderboardList();

	private void _leaderboardSaveAndList() {
		leaderboardSaveAndList();
	}
	private native void leaderboardSaveAndList();
    
	private void _levelSave() {
		levelSave();
	}
	private native void levelSave();

	private void _levelList() {
		levelList();
	}
	private native void levelList();

	private void _levelLoad() {
		levelLoad();
	}
	private native void levelLoad();
	
	private void _levelRate() {
		levelRate();
	}
	private native void levelRate();
	
	private void _loadPlays() {
		loadPlays();
	}
	private native void loadPlays();

	private void _loadPlaytime() {
		loadPlaytime();
	}
	private native void loadPlaytime();
	
	private void _loadViews() {
		loadViews();
	}
	private native void loadViews();
	
	
	private void _Freeze() {
		Freeze();
	}
	private native void Freeze();
	
	private void _UnFreeze() {
		UnFreeze();
	}
	private native void UnFreeze();
	
	private native void Destroy();
	
	public void printLog(String logLine)
	{
		//logBuffer += logLine + "\n";
		writeToBuffer(logBuffer + logLine + "\n");
		//L.log(logLine, this);
	}
	
	public void publishLog()
	{
		if(logBuffer.length() == 0)
		{
			return;
		}			
		L.log(logBuffer,this);
		//logBuffer = "";
		writeToBuffer("");
	}
	
	public synchronized void writeToBuffer(String text)
	{
		logBuffer = text;
	}
	
	private void startTimer(long delay, long period)
	{
       // timer
       //
       mPingTask = new TimerTask() {
           public void run() {
               mHandler.post(new Runnable() {
                   public void run() {
                	   publishLog();
                   }
               });
           }
       };
       mT = new Timer();
       mT.schedule(mPingTask, delay, period);
   }
	
	
	static {
		System.loadLibrary("Playtomic");
        System.loadLibrary("PlaytomicDemo");
        int somevar = 1;
        somevar = 2;
    }
}

