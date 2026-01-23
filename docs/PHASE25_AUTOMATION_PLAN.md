# Phase 2.5 Infrastructure Automation Plan

**Date:** January 23, 2026  
**Branch:** `dev/mfc-to-wxwidgets-tools`  
**Status:** Automation scripts created, ready for pilot  

---

## Overview

Phase 2.5 adds the missing infrastructure layer between Phase 2 (event handler stubs) and Phase 3 (business logic implementation):

**Phase 2:** Event handlers integrated → ✅ Dialogs compile  
**Phase 2.5:** Infrastructure implemented → ✅ Dialogs can transfer data  
**Phase 3:** Business logic ported → ✅ Dialogs function correctly  

---

## Automation Strategy

### Semi-Automated Approach (Recommended)

**Why not fully automated?**
- Complex C++ parsing requires robust AST analysis
- Custom initialization logic varies significantly between dialogs
- Manual review ensures correct business object mapping
- Pilot validation prevents systematic errors across all dialogs

**Automation Level:**
- ✅ 60-70%: Pattern extraction and code generation
- ⚠️ 30-40%: Manual conversion and verification

---

## Automation Scripts

### 1. analyze_mfc_dialog.py

**Purpose:** Extract infrastructure requirements from MFC dialog

**Input:**
- MFC .cpp file (implementation)
- MFC .h file (header)
- Class name

**Output:**
```
✓ Constructor parameters (business objects)
✓ Member variables (data storage)
✓ OnInitDialog implementation (control initialization)
✓ DoDataExchange DDX_ calls (data binding)
```

**Example:**
```bash
python3 scripts/analyze_mfc_dialog.py \
    Core/Tools/W3DView/EmitterGeneralPropPage.cpp \
    Core/Tools/W3DView/EmitterGeneralPropPage.h \
    EmitterGeneralPropPageClass
```

**Output:**
```
Constructor Parameters (1):
  - EmitterInstanceListClass *pemitter

Member Variables (8):
  - CComboBox m_RenderModeCombo
  - CSpinButtonCtrl m_LifetimeSpin
  - CString m_EmitterName
  - float m_Lifetime
  ...

✓ OnInitDialog Found (1241 characters)
✓ DoDataExchange Found (2 DDX_Control calls)
```

### 2. generate_phase25_infrastructure.py

**Purpose:** Generate wxWidgets infrastructure code from MFC analysis

**Input:**
- Same as analyze_mfc_dialog.py

**Output:**
- OnInitDialog → wxEVT_INIT_DIALOG handler
- DoDataExchange → TransferDataToWindow/FromWindow
- Updated constructor signature
- Event table entries
- Member variable declarations

**Example:**
```bash
python3 scripts/generate_phase25_infrastructure.py \
    Core/Tools/W3DView/EmitterGeneralPropPage.cpp \
    Core/Tools/W3DView/EmitterGeneralPropPage.h \
    EmitterGeneralPropPageClass > infrastructure.txt
```

**Generated Code:**
```cpp
// Phase 2.5: OnInitDialog → wxEVT_INIT_DIALOG
void EmitterGeneralPropPageClass::OnInitDialog(wxInitDialogEvent& event)
{
    // TODO: Convert SetDlgItemText(IDC_NAME_EDIT, m_EmitterName)
    // wxTextCtrl* ctrl = XRCCTRL(*this, "IDC_NAME_EDIT", wxTextCtrl);
    // if (ctrl) ctrl->SetValue(m_EmitterName);
    
    // TODO: Convert combo box population
    // ...
    
    event.Skip();
}

// Phase 2.5: TransferDataToWindow
bool EmitterGeneralPropPageClass::TransferDataToWindow()
{
    // TODO: DDX_Control(IDC_RENDER_MODE_COMBO, m_RenderModeCombo)
    // wxComboBox* ctrl = XRCCTRL(*this, "IDC_RENDER_MODE_COMBO", wxComboBox);
    // if (ctrl) ctrl->SetSelection(m_RenderMode);
    
    return true;
}

// Phase 2.5: Updated constructor
EmitterGeneralPropPageClass::EmitterGeneralPropPageClass(
    wxWindow *parent, 
    EmitterInstanceListClass *pemitter)
    : EmitterGeneralPropPageClassBase(parent)
    , pemitter(pemitter)  // Business object reference
{
    Centre();
}
```

---

## Implementation Workflow

### Phase 1: Pilot (3-5 Simple Dialogs)

**Objective:** Validate automation approach and refine patterns

**Select Simple Dialogs:**
1. Aboutbox (no business logic)
2. CameraDistance (simple float value)
3. DisplaySpeed (simple setting)
4. ColorForm (simple RGB input)
5. Opacity (simple transparency value)

**Process:**
```bash
# Step 1: Analyze MFC dialog
python3 scripts/analyze_mfc_dialog.py \
    <mfc_cpp> <mfc_h> <class_name> > analysis.txt

# Step 2: Review analysis output
cat analysis.txt

# Step 3: Generate infrastructure
python3 scripts/generate_phase25_infrastructure.py \
    <mfc_cpp> <mfc_h> <class_name> > infrastructure.cpp

# Step 4: Manual integration
# - Copy infrastructure code to dialog_wx.cpp
# - Uncomment and refine TODO items
# - Add member variables to dialog_wx.h
# - Test compilation

# Step 5: Verify
# - Compile dialog
# - Check for linking errors
# - Verify control access
# - Test data transfer (manual/unit test)
```

**Expected Results:**
- ✅ Dialogs compile
- ✅ Controls can be accessed
- ✅ Data can be transferred to/from controls
- ✅ Patterns validated for complex dialogs

**Duration:** 1-2 days

---

### Phase 2: Refine Automation (Iterative)

**Based on pilot learnings:**

1. **Improve Pattern Detection:**
   - Add more MFC → wxWidgets conversion patterns
   - Handle edge cases (custom controls, complex initialization)
   - Improve DDX_Text/DDX_Check parsing

2. **Enhance Code Generation:**
   - Better control type detection (ComboBox, ListBox, TreeCtrl)
   - Generate complete SetValue/GetValue calls (not just TODOs)
   - Add validation code generation
   - Handle CString → wxString conversions

3. **Add Verification:**
   - Syntax checking of generated code
   - Control ID validation against XRC
   - Member variable type checking

**Duration:** 1 day

---

### Phase 3: Batch Application (Remaining 54 Dialogs)

**Process:**
```bash
# Create batch script
cat > scripts/apply_phase25_to_all.sh << 'EOF'
#!/bin/bash

DIALOGS=(
    "AddToLineupDialog"
    "AnimatedSoundDialog"
    "BackgroundBmp"
    # ... all 54 remaining dialogs
)

for dialog in "${DIALOGS[@]}"; do
    echo "Processing $dialog..."
    
    # Analyze
    python3 scripts/analyze_mfc_dialog.py \
        Core/Tools/W3DView/${dialog}.cpp \
        Core/Tools/W3DView/${dialog}.h \
        ${dialog}Class > /tmp/${dialog}_analysis.txt
    
    # Generate
    python3 scripts/generate_phase25_infrastructure.py \
        Core/Tools/W3DView/${dialog}.cpp \
        Core/Tools/W3DView/${dialog}.h \
        ${dialog}Class > /tmp/${dialog}_infrastructure.cpp
    
    echo "  → Generated /tmp/${dialog}_infrastructure.cpp"
done
EOF

chmod +x scripts/apply_phase25_to_all.sh
./scripts/apply_phase25_to_all.sh
```

**Manual Integration:**
1. Review generated infrastructure for each dialog
2. Copy to corresponding _wx.cpp file
3. Uncomment and refine TODO items
4. Add member variables to _wx.h
5. Test compilation
6. Fix errors
7. Commit

**Duration:** 2-3 days (54 dialogs, ~15-20 per day)

---

### Phase 4: Testing & Verification

**Compilation Test:**
```bash
# Test all 59 dialogs compile
cd build
cmake --build . --target w3dview

# Expected: 59/59 dialogs compile successfully
```

**Data Transfer Test:**
```bash
# For each dialog, verify:
# 1. Controls are accessible via XRCCTRL
# 2. TransferDataToWindow populates controls
# 3. TransferDataFromWindow extracts data
# 4. No runtime errors

# Manual test or unit tests
```

**Duration:** 1-2 days

---

## Conversion Patterns

### MFC → wxWidgets Pattern Map

**Control Initialization:**
```cpp
// MFC:
SetDlgItemText(IDC_NAME_EDIT, m_Name);

// wxWidgets:
wxTextCtrl* ctrl = XRCCTRL(*this, "IDC_NAME_EDIT", wxTextCtrl);
if (ctrl) ctrl->SetValue(m_Name);
```

**ComboBox Population:**
```cpp
// MFC:
m_ComboBox.AddString("Item 1");
m_ComboBox.AddString("Item 2");
m_ComboBox.SetCurSel(0);

// wxWidgets:
wxComboBox* combo = XRCCTRL(*this, "IDC_COMBO", wxComboBox);
if (combo) {
    combo->Append("Item 1");
    combo->Append("Item 2");
    combo->SetSelection(0);
}
```

**Checkbox State:**
```cpp
// MFC:
SendDlgItemMessage(IDC_CHECK, BM_SETCHECK, BST_CHECKED);

// wxWidgets:
wxCheckBox* check = XRCCTRL(*this, "IDC_CHECK", wxCheckBox);
if (check) check->SetValue(true);
```

**Spin Control:**
```cpp
// MFC:
m_SpinCtrl.SetRange(0, 100);
m_SpinCtrl.SetPos(50);

// wxWidgets:
wxSpinCtrl* spin = XRCCTRL(*this, "IDC_SPIN", wxSpinCtrl);
if (spin) {
    spin->SetRange(0, 100);
    spin->SetValue(50);
}
```

**DDX_Text:**
```cpp
// MFC:
DDX_Text(pDX, IDC_EDIT, m_Value);

// wxWidgets TransferDataToWindow:
wxTextCtrl* ctrl = XRCCTRL(*this, "IDC_EDIT", wxTextCtrl);
if (ctrl) ctrl->SetValue(wxString::Format("%f", m_Value));

// wxWidgets TransferDataFromWindow:
wxTextCtrl* ctrl = XRCCTRL(*this, "IDC_EDIT", wxTextCtrl);
if (ctrl) ctrl->GetValue().ToDouble(&m_Value);
```

---

## Quality Checklist

After Phase 2.5 implementation, each dialog must pass:

- [ ] **Compilation:** No syntax errors
- [ ] **Linking:** No undefined references
- [ ] **Control Access:** All XRCCTRL calls succeed
- [ ] **Data Transfer:** TransferDataToWindow works
- [ ] **Data Extraction:** TransferDataFromWindow works
- [ ] **Initialization:** OnInitDialog populates controls
- [ ] **Business Object:** Constructor accepts business object
- [ ] **Member Variables:** All required members declared
- [ ] **Event Table:** EVT_INIT_DIALOG entry present
- [ ] **No Crashes:** Dialog can be shown without errors

---

## Timeline Estimate

| Phase | Task | Duration |
|-------|------|----------|
| **Pilot** | 5 simple dialogs manual | 1-2 days |
| **Refine** | Improve automation | 1 day |
| **Batch** | 54 dialogs semi-automated | 2-3 days |
| **Test** | Verification & fixes | 1-2 days |
| **Total** | **Phase 2.5 Complete** | **5-8 days** |

---

## Success Metrics

**Phase 2.5 is complete when:**
- ✅ All 59 dialogs compile
- ✅ All dialogs have OnInitDialog → wxEVT_INIT_DIALOG
- ✅ All dialogs have TransferDataToWindow/FromWindow
- ✅ All dialogs have business object constructors
- ✅ All controls can be accessed via XRCCTRL
- ✅ Data can flow to/from controls
- ✅ Ready for Phase 3 business logic implementation

---

## Automation Limitations

**What automation CANNOT do:**
- Complex business logic conversion
- Custom control initialization (requires domain knowledge)
- Validation rule implementation
- Error handling specifics
- Thread-safe data access
- Performance optimization

**These require manual implementation in Phase 3.**

---

## Next Steps

1. **Decision:** Approve Phase 2.5 pilot approach
2. **Action:** Select 3-5 simple dialogs for pilot
3. **Execute:** Run analysis and generation scripts
4. **Validate:** Manual integration and testing
5. **Refine:** Improve automation based on learnings
6. **Scale:** Apply to all 59 dialogs
7. **Verify:** Comprehensive testing
8. **Complete:** Phase 2.5 done, proceed to Phase 3

---

**Status:** Automation ready, awaiting pilot execution  
**Estimated Completion:** 5-8 days  
**Next Phase:** Phase 3 business logic implementation
