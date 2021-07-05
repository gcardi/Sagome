object frmeProtocolSettings: TfrmeProtocolSettings
  Left = 0
  Top = 0
  Width = 812
  Height = 172
  TabOrder = 0
  DesignSize = (
    812
    172)
  object Label5: TLabel
    Left = 16
    Top = 9
    Width = 39
    Height = 13
    Caption = 'Protocol'
  end
  object Label6: TLabel
    Left = 160
    Top = 8
    Width = 40
    Height = 13
    Caption = 'Slave ID'
  end
  object Label7: TLabel
    Left = 224
    Top = 8
    Width = 70
    Height = 13
    Caption = 'Transaction ID'
  end
  object cboxAutoIncTransactionID: TCheckBox
    Left = 312
    Top = 26
    Width = 145
    Height = 17
    Caption = 'Auto inc Transaction ID'
    Checked = True
    State = cbChecked
    TabOrder = 0
  end
  object comboboxProtocol: TComboBox
    Left = 16
    Top = 25
    Width = 129
    Height = 21
    Style = csDropDownList
    TabOrder = 1
  end
  object edtSlaveId: TEdit
    Left = 160
    Top = 24
    Width = 49
    Height = 21
    Alignment = taRightJustify
    NumbersOnly = True
    TabOrder = 2
    Text = '1'
  end
  object edtTransactionID: TEdit
    Left = 224
    Top = 24
    Width = 70
    Height = 21
    Alignment = taRightJustify
    NumbersOnly = True
    TabOrder = 3
    Text = '0'
  end
  object pgctrlProtocolSettings: TPageControl
    Left = 16
    Top = 57
    Width = 777
    Height = 97
    Anchors = [akLeft, akTop, akRight, akBottom]
    Style = tsButtons
    TabOrder = 4
    object tbshtProtocolSerialSettings: TTabSheet
      Caption = 'tbshtProtocolSerialSettings'
      TabVisible = False
      ExplicitWidth = 624
      inline frmeSerialSettings1: TfrmeSerialSettings
        Left = 3
        Top = 1
        Width = 305
        Height = 78
        AutoSize = True
        TabOrder = 0
        ExplicitLeft = 3
        ExplicitTop = 1
        ExplicitWidth = 305
        ExplicitHeight = 78
        inherited Label7: TLabel
          Left = 0
          Top = 41
          ExplicitLeft = 0
          ExplicitTop = 41
        end
        inherited Label8: TLabel
          Left = 64
          Top = 41
          ExplicitLeft = 64
          ExplicitTop = 41
        end
        inherited cmboxStopBits: TComboBox
          Left = 0
          Top = 57
          ExplicitLeft = 0
          ExplicitTop = 57
        end
        inherited cmboxDataBits: TComboBox
          Left = 64
          Top = 57
          ExplicitLeft = 64
          ExplicitTop = 57
        end
        inherited checkboxCancelTXEcho: TCheckBox
          Left = 137
          Top = 59
          ExplicitLeft = 137
          ExplicitTop = 59
        end
      end
    end
    object tbshtProtocolTCPIPSettings: TTabSheet
      Caption = 'tbshtProtocolTCPIPSettings'
      ImageIndex = 1
      TabVisible = False
      ExplicitWidth = 624
      object Label1: TLabel
        Left = 3
        Top = 2
        Width = 22
        Height = 13
        Caption = 'Host'
      end
      object Label2: TLabel
        Left = 136
        Top = 2
        Width = 20
        Height = 13
        Caption = 'Port'
      end
      object edtTCPIPHost: TEdit
        Left = 3
        Top = 18
        Width = 121
        Height = 21
        TabOrder = 0
        Text = 'localhost'
      end
      object edtTCPIPPort: TEdit
        Left = 136
        Top = 18
        Width = 49
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 1
        Text = '502'
      end
    end
  end
end
