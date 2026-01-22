# wxWidgets Dialog Implementation Template

This document provides a template and guidelines for implementing wxWidgets dialogs from XRC files.

## Pattern Overview

Each dialog consists of two classes:
1. **Base Class**: Loads from XRC and provides access to controls
2. **Derived Class**: Implements event handlers and data transfer

## File Structure

For a dialog named `FooDialog`:
- `FooDialog_wx.h` - Header file
- `FooDialog_wx.cpp` - Implementation file

## Header Template (FooDialog_wx.h)

```cpp
#pragma once

#include <wx/dialog.h>
#include <wx/button.h>
// Include other control types as needed

// Base class that loads from XRC
class FooDialogBase : public wxDialog
{
public:
    FooDialogBase() {}
    FooDialogBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        // Load dialog from XRC
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_DIALOG_NAME")) {
            return false;
        }

        // Get references to all controls
        m_okButton = XRCCTRL(*this, "IDOK", wxButton);
        m_cancelButton = XRCCTRL(*this, "IDCANCEL", wxButton);
        // Add other controls...

        return true;
    }

protected:
    // Control member variables
    wxButton *m_okButton;
    wxButton *m_cancelButton;
    // Add other controls...
};

// Derived class with functionality
class FooDialog : public FooDialogBase
{
public:
    FooDialog(wxWindow *parent);

    // Data members for dialog data exchange
    // int m_someValue;
    // bool m_someFlag;

protected:
    // Override for data transfer (if needed)
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

private:
    // Event handlers
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);
    // Add other event handlers...

    wxDECLARE_EVENT_TABLE();
};
```

## Implementation Template (FooDialog_wx.cpp)

```cpp
#include "FooDialog_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(FooDialog, FooDialogBase)
    EVT_BUTTON(XRCID("IDOK"), FooDialog::OnOK)
    EVT_BUTTON(XRCID("IDCANCEL"), FooDialog::OnCancel)
    // Add other event bindings...
wxEND_EVENT_TABLE()

FooDialog::FooDialog(wxWindow *parent)
    : FooDialogBase(parent)
    // Initialize data members
{
    // Additional initialization (set control ranges, etc.)
    
    // Load initial data into controls
    TransferDataToWindow();

    // Center on parent
    Centre();
}

bool FooDialog::TransferDataToWindow()
{
    // Transfer data from member variables to controls
    // Example: m_someControl->SetValue(m_someValue);
    
    return true;
}

bool FooDialog::TransferDataFromWindow()
{
    // Transfer data from controls to member variables
    // Example: m_someValue = m_someControl->GetValue();
    
    return true;
}

void FooDialog::OnOK(wxCommandEvent &event)
{
    // Validate and transfer data
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void FooDialog::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}
```

## Control Type Mappings

| MFC Control | wxWidgets Control | Header |
|-------------|-------------------|---------|
| CButton | wxButton | `<wx/button.h>` |
| CEdit | wxTextCtrl | `<wx/textctrl.h>` |
| CStatic (text) | wxStaticText | `<wx/stattext.h>` |
| CStatic (bitmap) | wxStaticBitmap | `<wx/statbmp.h>` |
| CCheckBox | wxCheckBox | `<wx/checkbox.h>` |
| CComboBox | wxComboBox | `<wx/combobox.h>` |
| CListBox | wxListBox | `<wx/listbox.h>` |
| CListCtrl | wxListCtrl | `<wx/listctrl.h>` |
| CTreeCtrl | wxTreeCtrl | `<wx/treectrl.h>` |
| CSliderCtrl | wxSlider | `<wx/slider.h>` |
| CSpinButtonCtrl | wxSpinButton | `<wx/spinbutt.h>` |

## Event Mappings

| MFC Message | wxWidgets Event | Event Table Macro |
|-------------|-----------------|-------------------|
| BN_CLICKED | wxEVT_BUTTON | EVT_BUTTON |
| EN_CHANGE | wxEVT_TEXT | EVT_TEXT |
| CBN_SELCHANGE | wxEVT_COMBOBOX | EVT_COMBOBOX |
| LBN_SELCHANGE | wxEVT_LISTBOX | EVT_LISTBOX |
| WM_HSCROLL | wxEVT_SLIDER | EVT_SLIDER |
| TVN_SELCHANGED | wxEVT_TREE_SEL_CHANGED | EVT_TREE_SEL_CHANGED |

## Data Transfer Pattern

### Simple Read-Only Dialogs
For dialogs that just display information:
- No TransferDataToWindow/FromWindow needed
- Just handle OK/Cancel buttons

### Dialogs with Input
For dialogs that accept user input:
1. Add data members for each piece of data
2. Implement TransferDataToWindow() to load initial values
3. Implement TransferDataFromWindow() to retrieve user input
4. Call TransferDataFromWindow() in OnOK before EndModal()

### Example: Simple Dialog
```cpp
// Read-only - just show and close
void AboutDialog::OnOK(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}
```

### Example: Input Dialog
```cpp
// With data validation and transfer
void SettingsDialog::OnOK(wxCommandEvent &event)
{
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}
```

## Testing Pattern

Each dialog can be tested independently:

```cpp
// In your application or test code:
FooDialog dialog(parentWindow);
if (dialog.ShowModal() == wxID_OK) {
    // User clicked OK
    int value = dialog.m_someValue;
    // Use the data...
}
```

## Usage in W3DView

Example of showing a dialog from menu:

```cpp
void W3DViewFrame::OnDisplaySpeed(wxCommandEvent &event)
{
    DisplaySpeedDialog dialog(this);
    
    // Set initial values
    dialog.m_speed = m_currentSpeed;
    dialog.m_blendFrames = m_blendEnabled;
    dialog.TransferDataToWindow();
    
    if (dialog.ShowModal() == wxID_OK) {
        // Get values from dialog
        m_currentSpeed = dialog.m_speed;
        m_blendEnabled = dialog.m_blendFrames;
        // Apply settings...
    }
}
```

## Implementation Priority

1. **Simple dialogs** (no input): AboutBox, etc.
2. **Settings dialogs** (basic input): DisplaySpeed, CameraDistance
3. **Property pages**: Convert to wxPropertySheetDialog
4. **Complex dialogs**: TextureMgr, BoneMgr, etc.

## Examples

See:
- `AboutDialog_wx.h/.cpp` - Simple read-only dialog
- `DisplaySpeedDialog_wx.h/.cpp` - Dialog with input controls
