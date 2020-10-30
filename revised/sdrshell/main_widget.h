#ifndef SDXCVR_MAINWIDGET_H
#define SDXCVR_MAINWIDGET_H

#include <qwidget.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qscrollview.h>
#include <qfont.h>
#include <qpixmap.h>
#include <qlistview.h>
#include <qlabel.h>
#include <qslider.h>
#include <qlineedit.h>
#include <qtimer.h>
#include <qdatetime.h>
#include <qfile.h>
#include <qsettings.h>
#include <qpainter.h>
#include <qimage.h>
#include <qlcdnumber.h>
#include <qheader.h>
#include <qdir.h>
#include <qtextedit.h>
#include <qscrollbar.h>
#include <qtabwidget.h>
#include <qspinbox.h>
#include <qtextedit.h>
#include <qgroupbox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>

#include <time.h>
#include <sys/timeb.h>

#include "spectrogram.h"
#include "spectrum.h"
#include "varilabel.h"
#include "memorycell.h"
#include "worldmap.h"
#include "pbscale.h"
#include "hamlibwrapper.h"

#define CMD_FILE "/dev/shm/SDRcommands"
#define MTR_FILE "/dev/shm/SDRmeter"
#define FFT_FILE "/dev/shm/SDRspectrum"

// DttSP constants
#define DEFSPEC (4096)
#define MAXRX (4)
#define RXMETERPTS (5)
#define TXMETERPTS (9)

#define DEFSPEC (4096)
#define SPECTRUM_HISTORY_SIZE (1000)

#define NUM_MODES 12

class Main_Widget : public QWidget
{
		Q_OBJECT

	private:
		QPushButton *quit_button;
		QScrollView *scroll_view;
		QFont *font;
		QLineEdit *cfgCallInput, *cfgLOFreqInput, *cfgIFreqInput, *cfgHamlibRigInput, *cfgHamlibSpeedInput, *cfgHamlibPortInput;
		QSpinBox *cfgIQPhaseInput, *cfgIQGainInput, *cfgUSBOffsetInput;
		QSpinBox *specCalSpinBox, *metrCalSpinBox, *cfgLSBOffsetInput;
		QSpinBox *cfgSlopeLowOffsetInput, *cfgSlopeHighOffsetInput;
		QPixmap *rxPix, *txPix;
		QFrame *trxFrame;
		hamlibWrapper *ourHamlibWrapper;

		const char* port;  //hamlib parameters.  
		QString portString;
		rig_model_t rig;
		QString rigString;
		int speed;
		QString speedString;
		bool useHamlib;
		void initHamlib ();
		bool useSlopeTune;
		bool muteXmit;

		bool useIF;
		int usbOffset;
		int lsbOffset;
		int slopeLowOffset;
		int slopeHighOffset;
		int slopeTuneOffset;
		int cwPitch;
		QLabel *cfgSlopeLowOffsetLabel;
		QLabel *cfgSlopeHighOffsetLabel;

		Varilabel *NR_label;
		Varilabel *ANF_label;
		Varilabel *NB_label;
		Varilabel *BIN_label;
		Varilabel *MUTE_label;
		Varilabel *SPEC_label;

		VariModelabel *LSB_label;
		VariModelabel *USB_label;
		VariModelabel *DSB_label;
		VariModelabel *AM_label;
		VariModelabel *CWL_label;
		VariModelabel *CWU_label;
		VariModelabel *SAM_label;
		VariModelabel *FMN_label;
		Varilabel *CFG_label;
		Varilabel *AGC_O_label, *AGC_L_label,
		*AGC_S_label, *AGC_M_label, *AGC_F_label;

		PassBandScale *pbscale;

		QFont *font1;
		QFontMetrics *font1Metrics;
		QLabel *signal_S;
		QLabel *signal_dBm;
		QLabel *qtrLabel;
		QLabel *CA_label;
		QLabel *iqGainLabel, *iqPhaseLabel;
		QLabel *callsignLabel;
		QLabel *cmdLabel;
		QLabel *CPU_label;
		QLabel *f_label;
		QLabel *logoLabel;
		QLabel *M_label;
		QLabel *AGC_label;
		QLabel *Spacer_label;

		QFrame *logoFrame;

		MemoryCell *f1_cell;
		MemoryCell *f2_cell;
		MemoryCell *f3_cell;
		MemoryCell *f4_cell;
		MemoryCell *f5_cell;
		MemoryCell *f6_cell;
		MemoryCell *f7_cell;
		MemoryCell *f8_cell;

		QLabel *af1_label;
		QLabel *af2_label;
		QLabel *af3_label;
		QLabel *af4_label;
		QLabel *af5_label;
		QLabel *af6_label;
		QLabel *af7_label;
		QLabel *af8_label;
		
		QLabel *cfgRigLabel;
		QLabel *cfgSpeedLabel;
		QLabel *cfgPortLabel;

		Spectrogram *spectrogram;
		Spectrum *spectrumFrame;
		QFrame *spectrogramFrame;
		QFrame *spectrumScale;
		QPixmap *spectrumPix;

		QFrame *ctlFrame;
		QFrame *ctlFrame2;
		QFrame *cfgFrame;
		QFrame *cmdFrame;
		QFrame *signalFrame;
		QFrame *signalBargraph[34];
		QFrame *map;
		QFrame *filterFrame;
		QColor *signalColor[34];
		//QString *modeName[NUM_MODES];
		QString stationCallsign;
		QString stationQTH;
		QLCDNumber *lcd;
		QTextStream cmdStream;
		QTextEdit *textFrame;
		QTable *configTable;

		QFrame *step_1Hz_frame;
		QFrame *step_10Hz_frame;
		QFrame *step_100Hz_frame;
		QFrame *step_1000Hz_frame;

		WorldMap *worldmap;

		unsigned long long int rx_f,rx_if;
		QString rx_f_string,rx_if_string;
		int sample_rate;
		int rx_delta_f, tuneStep;
		int *filter_l, *filter_h, filter_w;
		int USB_filter_l, USB_filter_h;
		int LSB_filter_l, LSB_filter_h;
		int DSB_filter_l, DSB_filter_h;
		int CWL_filter_l, CWL_filter_h;
		int CWU_filter_l, CWU_filter_h;
		int SAM_filter_l, SAM_filter_h;
		int FMN_filter_l, FMN_filter_h;
		int AM_filter_l, AM_filter_h;
		int s_dbm[34];
		int spec_r[120], spec_g[120], spec_b[120];
		rmode_t mode;
		int iqGain, iqPhase;
		int NR_state;
		int ANF_state;
		int NB_state;
		int BIN_state;
		int MUTE_state;
		int SPEC_state;
		int filterLine;
		int font1PointSize;
		int theme;
		int map_flag;
		int polyphaseFFT;
		int fftWindow;
		int spectrumType;
		int agcType;

		float spectrum[DEFSPEC];
		float oscope[DEFSPEC];
		float specApertureLow, specApertureHigh;
		float specCal;
		float metrCal;

		int spectrum_history[SPECTRUM_HISTORY_SIZE][DEFSPEC];
		int spectrum_head;

		float loadavg;
		double my_lon, my_lat;

		FILE *cmdFile;
		FILE *mtrFile;
		FILE *fftFile;

		FILE *loadavg_stream;

		enum kb_state { RX_F, TX_F, FILTER_L, FILTER_H };
		enum modes
		{ LSB, USB, DSB, CWL, CWU, FMN, AM, DIGU, SPEC, DIGL, SAM, DRM }; 
		enum spec_type { SEMI_RAW, PRE_FILT, POST_FILT };

		typedef enum _windowtype {
		    RECTANGULAR_WINDOW,
		    HANNING_WINDOW,
		    WELCH_WINDOW,
		    PARZEN_WINDOW,
		    BARTLETT_WINDOW,
		    HAMMING_WINDOW,
		    BLACKMAN2_WINDOW,
		    BLACKMAN3_WINDOW,
		    BLACKMAN4_WINDOW,
		    EXPONENTIAL_WINDOW,
		    RIEMANN_WINDOW,
		    BLACKMANHARRIS_WINDOW,
		    NUTTALL_WINDOW,
	} Windowtype;

		void initConstants();
		void rx_cmd ( int );
		void process_key ( int );
		void setRxFrequency();
		void setDefaultRxFrequency();
		void loadSettings();
		void saveSettings();
		void setScrollBarColors ( QScrollBar * );
		void setCA_label();
		void set_NR ( int );

		void set_ANF ( int );
		void set_NB ( int );
		void set_BIN ( int );
		void set_SPEC ( int );
		void setIQGain();
		void setIQPhase();
		void drawSpectrogram();
		void drawSpectrogram_2();
		void drawSpectrumScale();
		void drawSpectrumScale_2();
		void drawPassBandScale();
		void setTheme ( int );
		void updateLayout();
		void loadMemoryCells();

	public:
		Main_Widget ( QWidget *parent = 0, const char *name = 0 );

	public slots:
		void finish();
		void readMeter();
		void readSpectrum();
		//void processCmdLine();
		void spectrogramClicked ( int );
		void plotSpectrum ( int );
		void tune ( int );
		void processorLoad();

		void setTuneStep ( int );
		void toggle_NR ( int );
		void toggle_ANF ( int );
		void toggle_NB ( int );
		void toggle_BIN ( int );
		void toggle_MUTE ( int );
		void toggle_SPEC ( int );

		void setFilter_l ( int );
		void setFilter_h ( int );
		void setMode ( rmode_t, bool );
		void setFilter();
		void f_at_mousepointer ( int );
		void setLowerFilterScale ( int );
		void setUpperFilterScale ( int );
		void setCfg ( int );

		void readMem ( MemoryCell * );
		void writeMem ( MemoryCell * );
		void displayMem ( MemoryCell * );
		void displayNCO ( int );

		void updateCallsign();
		void updateLOFreq();
		void updateIFreq();
		void updateUSBOffset ( int );
		void updateLSBOffset ( int );
		void updateSlopeHighOffset ( int offset );
		void updateSlopeLowOffset ( int offset );	
		void updateHamlib();
		void updateIQGain ( int );
		void updateIQPhase ( int );
		void setPolyFFT ( int );
		void setFFTWindow ( int );
		void setSpectrumType ( int );
		void setAGC ( int );
		void calibrateSpec ( int );
		void calibrateMetr ( int );
		
		void set_MUTE ( int );
		void setOurRxFrequency ( double );
		void setIF ( bool );
		void setHamlib ( bool );
		void setSlopeLowOffset ( int );
		void setSlopeHighOffset (int );
		void setSlopeTune ( bool );
		void setCWPitch ( int );
		void setMuteXmit ( bool );

	protected:
		void keyPressEvent ( QKeyEvent * );
		void paintEvent ( QPaintEvent * );
		void focusInEvent ( QFocusEvent * );
		void focusOutEvent ( QFocusEvent * );
		void closeEvent ( QCloseEvent * );
		
	signals:
		void changeRigMode (rmode_t, pbwidth_t );
		void changeSlopeTune ( bool );
		void toggleHamlibButton ( bool );
		void tellMuteXmit ( bool );
};
#endif
