object frmeModbusFunctions: TfrmeModbusFunctions
  Left = 0
  Top = 0
  Width = 533
  Height = 120
  TabOrder = 0
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 533
    Height = 17
    Align = alTop
    BevelOuter = bvNone
    Caption = 'Modbus functions'
    TabOrder = 0
  end
  object pgctrlFunctions: TPageControl
    Left = 0
    Top = 17
    Width = 533
    Height = 103
    ActivePage = tbshtFnPresetMultipleRegisters
    Align = alClient
    TabOrder = 1
    object tbshrFnReadHoldingRegisters: TTabSheet
      Caption = 'Read Holding Regs'
      object Label3: TLabel
        Left = 100
        Top = 3
        Width = 39
        Height = 13
        Caption = 'Address'
      end
      object Label4: TLabel
        Left = 169
        Top = 3
        Width = 54
        Height = 13
        Caption = 'Point count'
      end
      object Button2: TButton
        Left = 19
        Top = 15
        Width = 59
        Height = 25
        Caption = 'Send'
        TabOrder = 0
      end
      object edtReadHoldingRegistersAddr: TEdit
        Left = 97
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 1
        Text = '0'
      end
      object edtReadHoldingRegistersPtCnt: TEdit
        Left = 166
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 2
        Text = '1'
      end
    end
    object tbshrFnReadInputRegisters: TTabSheet
      Caption = 'Read Input Registers'
      ImageIndex = 3
      object Label12: TLabel
        Left = 100
        Top = 3
        Width = 39
        Height = 13
        Caption = 'Address'
      end
      object Label13: TLabel
        Left = 169
        Top = 3
        Width = 54
        Height = 13
        Caption = 'Point count'
      end
      object Button6: TButton
        Left = 19
        Top = 15
        Width = 59
        Height = 25
        Caption = 'Send'
        TabOrder = 0
      end
      object edtReadInputRegistersAddr: TEdit
        Left = 97
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 1
        Text = '0'
      end
      object edtReadInputRegistersPtCnt: TEdit
        Left = 166
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 2
        Text = '1'
      end
    end
    object tbshtFnPresetSingleRegister: TTabSheet
      Caption = 'Preset Single Reg'
      ImageIndex = 1
      object Label8: TLabel
        Left = 100
        Top = 3
        Width = 39
        Height = 13
        Caption = 'Address'
      end
      object Label9: TLabel
        Left = 169
        Top = 3
        Width = 26
        Height = 13
        Caption = 'Value'
      end
      object Label2: TLabel
        Left = 349
        Top = 3
        Width = 46
        Height = 13
        Caption = 'Time (ms)'
      end
      object Button3: TButton
        Left = 19
        Top = 15
        Width = 59
        Height = 25
        Caption = 'Send'
        TabOrder = 0
      end
      object edtPresetSingleRegisterAddr: TEdit
        Left = 97
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 1
        Text = '0'
      end
      object edtPresetSingleRegisterValue: TEdit
        Left = 166
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 2
        Text = '1'
      end
      object cboxPresetSingleRegisterPulsed: TCheckBox
        Left = 256
        Top = 19
        Width = 97
        Height = 17
        Caption = 'Pulsed'
        TabOrder = 3
      end
      object edtPresetSingleRegisterPulseTime: TEdit
        Left = 347
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 4
        Text = '1000'
      end
    end
    object tbshtFnPresetMultipleRegisters: TTabSheet
      Caption = 'Preset Multiple Regs'
      ImageIndex = 2
      DesignSize = (
        525
        75)
      object Label10: TLabel
        Left = 100
        Top = 3
        Width = 39
        Height = 13
        Caption = 'Address'
      end
      object Label11: TLabel
        Left = 305
        Top = 3
        Width = 23
        Height = 13
        Caption = 'Data'
      end
      object Label1: TLabel
        Left = 234
        Top = 3
        Width = 46
        Height = 13
        Caption = 'Time (ms)'
      end
      object Button5: TButton
        Left = 19
        Top = 15
        Width = 59
        Height = 25
        Caption = 'Send'
        TabOrder = 0
      end
      object edtPresetMultipleRegistersAddr: TEdit
        Left = 97
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 1
        Text = '0'
      end
      object edtPresetMultipleRegistersData: TEdit
        Left = 302
        Top = 17
        Width = 203
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 2
        Text = '1, 2, 3, 4, 5, 6'
      end
      object cboxPresetMultipleRegisterPulsed: TCheckBox
        Left = 169
        Top = 19
        Width = 57
        Height = 17
        Caption = 'Pulsed'
        TabOrder = 3
      end
      object edtPresetMultipleRegisterPulseTime: TEdit
        Left = 232
        Top = 17
        Width = 55
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 4
        Text = '1000'
      end
    end
  end
end
