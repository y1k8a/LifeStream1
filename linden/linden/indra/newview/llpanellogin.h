/** 
 * @file llpanellogin.h
 * @brief Login username entry fields.
 *
 * $LicenseInfo:firstyear=2002&license=viewergpl$
 * 
 * Copyright (c) 2002-2008, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#ifndef LL_LLPANELLOGIN_H
#define LL_LLPANELLOGIN_H

#include "llpanel.h"
#include "llmemory.h"			// LLPointer<>
#include "llmediactrl.h"	// LLMediaCtrlObserver

class LLUIImage;


class LLPanelLogin:	
	public LLPanel,
	public LLViewerMediaObserver
{
	LOG_CLASS(LLPanelLogin);
public:
	LLPanelLogin(const LLRect &rect, BOOL show_server, 
				void (*callback)(S32 option, void* user_data),
				void *callback_data);
	~LLPanelLogin();

	virtual BOOL handleKeyHere(KEY key, MASK mask);
	virtual void draw();
	virtual void setFocus( BOOL b );

	static void show(const LLRect &rect, BOOL show_server, 
		void (*callback)(S32 option, void* user_data), 
		void* callback_data);

	// Sets the login screen's name and password editors. Remember password checkbox is set via gSavedSettings "RememberPassword"
	static void setFields(const std::string& firstname, const std::string& lastname, const std::string& password);
	static void setFields(const std::string& username, const std::string& password);

	static void addServer(const std::string& server);
	static void refreshLocation( bool force_visible );
	// Updates grid combo at login screen with a specific nick. Use an empty string to refresh
	static void updateGridCombo(std::string grid_nick);

	static void getFields(std::string *firstname, std::string *lastname,
						  std::string *password);

	static BOOL isGridComboDirty();
	static void getLocation(std::string &location);

	static void close();

	void setSiteIsAlive( bool alive );

	static void loadLoginForm();
	static void loadLoginPage();	
	static void refreshLoginPage();
	static void giveFocus();
	static void setAlwaysRefresh(bool refresh); 
	
	// inherited from LLViewerMediaObserver
	/*virtual*/ void handleMediaEvent(LLPluginClassMedia* self, EMediaEvent event);

	/// Load the news bar web page, return true if successful.
	bool loadNewsBar();

private:
	static void onClickConnect(void*);
	static void onClickGrid(void*);
	static void onClickNewAccount(void*);
	static bool newAccountAlertCallback(const LLSD& notification, const LLSD& response);
	static void onClickQuit(void*);
	static void onClickVersion(void*);
	static void onPasswordChanged(LLUICtrl* caller, void* user_data);
	static void onClickForgotPassword(void*);
	static void onPassKey(LLLineEditor* caller, void* user_data);
	static void onSelectServer(LLUICtrl*, void*);
	static void onServerComboLostFocus(LLFocusableElement*, void*);

	// converts the following login name formats into valid firstname lastname combos:
	// username
	// username.Resident
	// first.last
	// first+" "+last
	// "     "+first+"    "+last+"     "
	// returns true if name conversion successful
	static bool convertUsernameToLegacy(std::string& username, std::string& firstname, std::string& lastname);

	// set the password for the login screen
	static void setPassword(const std::string& password);
	
	LLPointer<LLUIImage> mLogoImage;

	void			(*mCallback)(S32 option, void *userdata);
	void*			mCallbackData;

	std::string mActualPassword;

	static LLPanelLogin* sInstance;
	static BOOL		sCapslockDidNotification;
	BOOL			mHtmlAvailable;
};

std::string load_password_from_disk(void);
void save_password_to_disk(const char* hashed_password);

#endif
