object frmeSerialSettings: TfrmeSerialSettings
  Left = 0
  Top = 0
  Width = 554
  Height = 37
  AutoSize = True
  TabOrder = 0
  object Label5: TLabel
    Left = 152
    Top = 0
    Width = 30
    Height = 13
    Caption = 'Speed'
  end
  object Label6: TLabel
    Left = 248
    Top = 0
    Width = 28
    Height = 13
    Caption = 'Parity'
  end
  object Label7: TLabel
    Left = 320
    Top = 0
    Width = 42
    Height = 13
    Caption = 'Stop bits'
  end
  object Label8: TLabel
    Left = 384
    Top = 0
    Width = 43
    Height = 13
    Caption = 'Data bits'
  end
  object Label1: TLabel
    Left = 0
    Top = 0
    Width = 49
    Height = 13
    Caption = 'Port name'
  end
  object cmboxSpeed: TComboBox
    Left = 152
    Top = 16
    Width = 81
    Height = 21
    Style = csDropDownList
    DropDownCount = 12
    ItemIndex = 11
    TabOrder = 0
    Text = '115200'
    Items.Strings = (
      '110'
      '300'
      '600'
      '1200'
      '2400'
      '4800'
      '9600'
      '14400'
      '19200'
      '38400'
      '57600'
      '115200'
      '128000'
      '256000')
  end
  object cmboxParity: TComboBox
    Left = 248
    Top = 16
    Width = 57
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 1
    Text = 'None'
    Items.Strings = (
      'None'
      'Odd  '
      'Even '
      'Mark '
      'Space')
  end
  object cmboxStopBits: TComboBox
    Left = 320
    Top = 16
    Width = 52
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 2
    Text = '1'
    Items.Strings = (
      '1'
      '1.5'
      '2')
  end
  object cmboxDataBits: TComboBox
    Left = 384
    Top = 16
    Width = 57
    Height = 21
    Style = csDropDownList
    ItemIndex = 3
    TabOrder = 3
    Text = '8'
    Items.Strings = (
      '5'
      '6'
      '7'
      '8')
  end
  object checkboxCancelTXEcho: TCheckBox
    Left = 457
    Top = 18
    Width = 97
    Height = 17
    Caption = 'Cancel TX echo'
    TabOrder = 4
  end
  object cmboxPortName: TComboBox
    Left = 0
    Top = 16
    Width = 137
    Height = 21
    DropDownCount = 12
    TabOrder = 5
  end
end
