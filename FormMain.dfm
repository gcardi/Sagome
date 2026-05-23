object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'frmMain'
  ClientHeight = 726
  ClientWidth = 958
  Color = clBtnFace
  CustomTitleBar.Control = TitleBarPanel1
  CustomTitleBar.Enabled = True
  CustomTitleBar.Height = 31
  CustomTitleBar.BackgroundColor = clWhite
  CustomTitleBar.ForegroundColor = 65793
  CustomTitleBar.InactiveBackgroundColor = clWhite
  CustomTitleBar.InactiveForegroundColor = 10066329
  CustomTitleBar.ButtonForegroundColor = 65793
  CustomTitleBar.ButtonBackgroundColor = clWhite
  CustomTitleBar.ButtonHoverForegroundColor = 65793
  CustomTitleBar.ButtonHoverBackgroundColor = 16053492
  CustomTitleBar.ButtonPressedForegroundColor = 65793
  CustomTitleBar.ButtonPressedBackgroundColor = 15395562
  CustomTitleBar.ButtonInactiveForegroundColor = 10066329
  CustomTitleBar.ButtonInactiveBackgroundColor = clWhite
  Constraints.MinHeight = 600
  Constraints.MinWidth = 970
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  GlassFrame.Enabled = True
  GlassFrame.Top = 31
  ShowHint = True
  StyleElements = [seFont, seClient]
  OnShow = FormShow
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 324
    Width = 958
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ResizeStyle = rsUpdate
    ExplicitLeft = -8
    ExplicitTop = 223
    ExplicitWidth = 664
  end
  object TitleBarPanel1: TTitleBarPanel
    Left = 0
    Top = 0
    Width = 958
    Height = 30
    CustomButtons = <
      item
        ButtonType = sbCustom
        Hint = 'Cambia tema'
        Width = 46
        OnPaint = TitleBarPanel1CustomButtons0Paint
        OnClick = TitleBarPanel1CustomButtons0Click
      end>
    DesignSize = (
      958
      30)
    object lblTitleBarCaption: TLabel
      Left = 36
      Top = 0
      Width = 600
      Height = 30
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      EllipsisPosition = epEndEllipsis
      Transparent = True
      Layout = tlCenter
    end
  end
  object pnlLog: TPanel
    Left = 0
    Top = 468
    Width = 958
    Height = 239
    Margins.Left = 8
    Margins.Top = 0
    Margins.Right = 8
    Margins.Bottom = 8
    Align = alClient
    BevelOuter = bvNone
    Caption = 'pnlLog'
    Constraints.MinHeight = 100
    ShowCaption = False
    TabOrder = 0
    inline frmeLog1: TfrmeLog
      Left = 0
      Top = 0
      Width = 958
      Height = 239
      Align = alClient
      TabOrder = 0
      ExplicitWidth = 958
      ExplicitHeight = 239
      inherited RichEdit1: TRichEdit
        Width = 958
        Height = 222
        ScrollBars = ssBoth
        ExplicitWidth = 958
        ExplicitHeight = 222
      end
      inherited Panel2: TPanel
        Width = 958
        ExplicitWidth = 958
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 707
    Width = 958
    Height = 19
    AutoHint = True
    Panels = <>
    SimplePanel = True
  end
  object pnlTrials: TPanel
    Left = 0
    Top = 327
    Width = 958
    Height = 141
    Align = alTop
    BevelOuter = bvNone
    Caption = 'pnlTrials'
    ShowCaption = False
    TabOrder = 2
    object Panel6: TPanel
      Left = 0
      Top = 0
      Width = 958
      Height = 17
      Align = alTop
      Caption = 'Trials'
      TabOrder = 0
    end
    object Panel3: TPanel
      Left = 0
      Top = 17
      Width = 664
      Height = 124
      Align = alClient
      BevelOuter = bvNone
      Caption = 'Panel3'
      ShowCaption = False
      TabOrder = 1
      object PageControl1: TPageControl
        Left = 0
        Top = 0
        Width = 625
        Height = 124
        ActivePage = tbshtPGCMirato
        Align = alLeft
        TabOrder = 0
        object tbshtPGCMirato: TTabSheet
          Caption = 'PGC Mirato'
          ImageIndex = 2
          object Button2: TButton
            Left = 22
            Top = 14
            Width = 155
            Height = 25
            Action = actGareProvaPGCMiratoStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button17: TButton
            Left = 183
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPGCMiratoStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button18: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPGCMiratoStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object tbshtPGCCelere: TTabSheet
          Caption = 'PGC Celere'
          ImageIndex = 3
          object Button6: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGareProvaPGCCelereStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button15: TButton
            Left = 183
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPGCCelereStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button16: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPGCCelereStart
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object tbshtPS150sec: TTabSheet
          Caption = 'PS 150"'
          ImageIndex = 6
          object Button9: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGareProvaPS150
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button21: TButton
            Left = 183
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPS150
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button22: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPS150
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object tbshtPS20sec: TTabSheet
          Caption = 'PS 20"'
          ImageIndex = 5
          object Button10: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPS20
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button20: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPS20
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
        end
        object tbshtPS10sec: TTabSheet
          Caption = 'PS 10"'
          ImageIndex = 4
          object Button11: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPS10
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button19: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPS10
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
        end
        object tbshtPA8sec: TTabSheet
          Caption = 'PA 8"'
          ImageIndex = 9
          object Button12: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGareProvaPA8
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button25: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPA8
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button26: TButton
            Left = 183
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPA8
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object tbshtPA6sec: TTabSheet
          Caption = 'PA 6"'
          ImageIndex = 8
          object Button13: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPA6
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button24: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPA6
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
        end
        object tbshtPA4sec: TTabSheet
          Caption = 'PA 4"'
          ImageIndex = 7
          object Button14: TButton
            Left = 14
            Top = 14
            Width = 155
            Height = 25
            Action = actGarePrimaPA4
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button23: TButton
            Left = 14
            Top = 54
            Width = 155
            Height = 25
            Action = actGareProssimaPA4
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
        end
        object tbshtModbus: TTabSheet
          Caption = 'Modbus'
          TabVisible = False
          inline frmeModbusFunctions1: TfrmeModbusFunctions
            Left = 0
            Top = 0
            Width = 617
            Height = 96
            Align = alClient
            TabOrder = 0
            ExplicitWidth = 617
            ExplicitHeight = 96
            inherited Panel4: TPanel
              Width = 617
              Caption = 'Functions'
              ExplicitWidth = 617
            end
            inherited pgctrlFunctions: TPageControl
              Width = 617
              Height = 79
              ActivePage = frmeModbusFunctions1.tbshtFnPresetSingleRegister
              ExplicitWidth = 617
              ExplicitHeight = 79
              inherited tbshrFnReadHoldingRegisters: TTabSheet
                ExplicitTop = 24
                ExplicitHeight = 75
                inherited Label3: TLabel
                  Width = 39
                  Height = 13
                  ExplicitWidth = 39
                  ExplicitHeight = 13
                end
                inherited Label4: TLabel
                  Width = 54
                  Height = 13
                  ExplicitWidth = 54
                  ExplicitHeight = 13
                end
                inherited Button2: TButton
                  Action = actFnReadHoldingRegisters
                  Caption = 'Read'
                end
              end
              inherited tbshrFnReadInputRegisters: TTabSheet
                ExplicitTop = 24
                ExplicitHeight = 75
                inherited Label12: TLabel
                  Width = 39
                  Height = 13
                  ExplicitWidth = 39
                  ExplicitHeight = 13
                end
                inherited Label13: TLabel
                  Width = 54
                  Height = 13
                  ExplicitWidth = 54
                  ExplicitHeight = 13
                end
                inherited Button6: TButton
                  Action = actFnReadInputRegisters
                  Caption = 'Read'
                end
              end
              inherited tbshtFnPresetSingleRegister: TTabSheet
                ExplicitTop = 24
                ExplicitWidth = 609
                ExplicitHeight = 51
                inherited Label8: TLabel
                  Width = 39
                  Height = 13
                  ExplicitWidth = 39
                  ExplicitHeight = 13
                end
                inherited Label9: TLabel
                  Width = 26
                  Height = 13
                  ExplicitWidth = 26
                  ExplicitHeight = 13
                end
                inherited Label2: TLabel
                  Width = 46
                  Height = 13
                  ExplicitWidth = 46
                  ExplicitHeight = 13
                end
                inherited Button3: TButton
                  Action = actFnPresetSingleRegister
                  Caption = 'Preset'
                end
              end
              inherited tbshtFnPresetMultipleRegisters: TTabSheet
                ExplicitTop = 24
                ExplicitHeight = 75
                inherited Label10: TLabel
                  Width = 39
                  Height = 13
                  ExplicitWidth = 39
                  ExplicitHeight = 13
                end
                inherited Label11: TLabel
                  Width = 23
                  Height = 13
                  ExplicitWidth = 23
                  ExplicitHeight = 13
                end
                inherited Label1: TLabel
                  Width = 46
                  Height = 13
                  ExplicitWidth = 46
                  ExplicitHeight = 13
                end
              end
            end
          end
        end
      end
    end
    object pnlStopwatch: TPanel
      Left = 664
      Top = 17
      Width = 294
      Height = 124
      Align = alRight
      BevelOuter = bvNone
      Caption = 'pnlStopwatch'
      ShowCaption = False
      TabOrder = 2
      DesignSize = (
        294
        124)
      object lblStopwatch: TLabel
        Left = -9
        Top = 32
        Width = 261
        Height = 82
        Alignment = taCenter
        Anchors = [akTop, akRight]
        AutoSize = False
        Caption = '00:00:0'
        Color = clBlack
        Constraints.MaxHeight = 148
        Constraints.MaxWidth = 512
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -64
        Font.Name = 'Arial'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        Transparent = False
        Layout = tlCenter
      end
    end
  end
  object pnlTop: TPanel
    Left = 0
    Top = 30
    Width = 958
    Height = 294
    Align = alTop
    Caption = 'pnlTop'
    Constraints.MinHeight = 229
    ShowCaption = False
    TabOrder = 3
    object PageControl2: TPageControl
      Left = 1
      Top = 1
      Width = 956
      Height = 292
      ActivePage = TabSheet1
      Align = alClient
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = 'Shooting targets'
        object Label3: TLabel
          Left = 18
          Top = 107
          Width = 16
          Height = 13
          Alignment = taRightJustify
          Caption = '1-5'
        end
        object Label4: TLabel
          Left = 12
          Top = 140
          Width = 22
          Height = 13
          Alignment = taRightJustify
          Caption = '6-10'
        end
        object PaintBox6_10: TPaintBox
          Tag = 1
          Left = 163
          Top = 137
          Width = 238
          Height = 21
          OnPaint = PaintBox1_5Paint
        end
        object PaintBox1_5: TPaintBox
          Left = 163
          Top = 104
          Width = 238
          Height = 21
          OnPaint = PaintBox1_5Paint
        end
        object Label8: TLabel
          Left = 131
          Top = 107
          Width = 23
          Height = 13
          Alignment = taRightJustify
          Caption = 'Outs'
        end
        object Label9: TLabel
          Left = 131
          Top = 140
          Width = 23
          Height = 13
          Alignment = taRightJustify
          Caption = 'Outs'
        end
        object GroupBox1: TGroupBox
          Left = 195
          Top = 3
          Width = 169
          Height = 54
          Caption = 'Communication'
          TabOrder = 0
          object Button1: TButton
            Left = 13
            Top = 19
            Width = 65
            Height = 25
            Action = actOpen
            TabOrder = 0
          end
          object Button4: TButton
            Left = 89
            Top = 19
            Width = 66
            Height = 25
            Action = actClose
            TabOrder = 1
          end
        end
        object ToggleSwitch1: TToggleSwitch
          Left = 40
          Top = 104
          Width = 50
          Height = 20
          Action = actGareEnb1_5
          ShowStateCaption = False
          StyleName = 'Windows'
          TabOrder = 1
        end
        object ToggleSwitch2: TToggleSwitch
          Left = 40
          Top = 137
          Width = 50
          Height = 20
          Action = actGareEnb6_10
          Color = clBtnFace
          ParentShowHint = False
          ShowHint = True
          ShowStateCaption = False
          StyleName = 'Windows'
          TabOrder = 2
        end
        object GroupBox2: TGroupBox
          Left = 12
          Top = 3
          Width = 169
          Height = 87
          Caption = 'Manual'
          TabOrder = 3
          object Button3: TButton
            Left = 13
            Top = 20
            Width = 66
            Height = 25
            Action = actGareResetCycle
            ParentShowHint = False
            ShowHint = False
            TabOrder = 0
          end
          object Button7: TButton
            Left = 13
            Top = 51
            Width = 66
            Height = 25
            Action = actGareApertura
            ParentShowHint = False
            ShowHint = False
            TabOrder = 1
          end
          object Button8: TButton
            Left = 90
            Top = 51
            Width = 66
            Height = 25
            Action = actGareChiusura
            ParentShowHint = False
            ShowHint = False
            TabOrder = 2
          end
        end
        object Button5: TButton
          Left = 102
          Top = 23
          Width = 66
          Height = 25
          Action = actGareStop
          ParentShowHint = False
          ShowHint = False
          TabOrder = 4
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Protocol'
        ImageIndex = 1
        object Panel5: TPanel
          AlignWithMargins = True
          Left = 16
          Top = 16
          Width = 916
          Height = 105
          Margins.Left = 16
          Margins.Top = 16
          Margins.Right = 16
          Align = alTop
          BevelOuter = bvNone
          Caption = 'Panel5'
          ShowCaption = False
          TabOrder = 0
          object pgctrlProtocolSettings: TPageControl
            Left = 0
            Top = 49
            Width = 916
            Height = 56
            ActivePage = tbshtProtocolDummySettings
            Align = alClient
            Style = tsButtons
            TabOrder = 0
            object tbshtProtocolSerialSettings: TTabSheet
              Caption = 'tbshtProtocolSerialSettings'
              TabVisible = False
              inline frmeSerialSettings1: TfrmeSerialSettings
                Left = 3
                Top = 1
                Width = 554
                Height = 37
                AutoSize = True
                TabOrder = 0
                ExplicitLeft = 3
                ExplicitTop = 1
                inherited Label5: TLabel
                  Width = 30
                  Height = 13
                  ExplicitWidth = 30
                  ExplicitHeight = 13
                end
                inherited Label6: TLabel
                  Width = 28
                  Height = 13
                  ExplicitWidth = 28
                  ExplicitHeight = 13
                end
                inherited Label7: TLabel
                  Width = 42
                  Height = 13
                  ExplicitWidth = 42
                  ExplicitHeight = 13
                end
                inherited Label8: TLabel
                  Width = 43
                  Height = 13
                  ExplicitWidth = 43
                  ExplicitHeight = 13
                end
                inherited Label1: TLabel
                  Width = 49
                  Height = 13
                  ExplicitWidth = 49
                  ExplicitHeight = 13
                end
                inherited cmboxSpeed: TComboBox
                  Height = 21
                end
                inherited cmboxParity: TComboBox
                  Height = 21
                end
                inherited cmboxStopBits: TComboBox
                  Height = 21
                  TabOrder = 3
                end
                inherited cmboxDataBits: TComboBox
                  Height = 21
                  TabOrder = 4
                end
                inherited checkboxCancelTXEcho: TCheckBox
                  TabOrder = 2
                end
                inherited cmboxPortName: TComboBox
                  Height = 21
                  ExplicitHeight = 21
                end
              end
            end
            object tbshtProtocolTCPIPSettings: TTabSheet
              Caption = 'tbshtProtocolTCPIPSettings'
              ImageIndex = 1
              TabVisible = False
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
            object tbshtProtocolDummySettings: TTabSheet
              Caption = 'tbshtProtocolDummySettings'
              ImageIndex = 2
              TabVisible = False
            end
          end
          object Panel1: TPanel
            Left = 0
            Top = 0
            Width = 916
            Height = 49
            Align = alTop
            BevelOuter = bvNone
            Caption = 'Panel1'
            ShowCaption = False
            TabOrder = 1
            object Label5: TLabel
              Left = 0
              Top = 1
              Width = 39
              Height = 13
              Caption = 'Protocol'
            end
            object Label6: TLabel
              Left = 144
              Top = 0
              Width = 40
              Height = 13
              Caption = 'Slave ID'
            end
            object Label7: TLabel
              Left = 208
              Top = 0
              Width = 70
              Height = 13
              Caption = 'Transaction ID'
            end
            object cboxAutoIncTransactionID: TCheckBox
              Left = 296
              Top = 18
              Width = 145
              Height = 17
              Caption = 'Auto inc Transaction ID'
              Checked = True
              State = cbChecked
              TabOrder = 0
            end
            object comboboxProtocol: TComboBox
              Left = 0
              Top = 17
              Width = 129
              Height = 21
              Style = csDropDownList
              TabOrder = 1
              OnChange = comboboxProtocolChange
            end
            object edtSlaveId: TEdit
              Left = 144
              Top = 16
              Width = 49
              Height = 21
              Alignment = taRightJustify
              NumbersOnly = True
              TabOrder = 2
              Text = '1'
            end
            object edtTransactionID: TEdit
              Left = 208
              Top = 16
              Width = 70
              Height = 21
              Alignment = taRightJustify
              NumbersOnly = True
              TabOrder = 3
              Text = '0'
            end
          end
        end
      end
      object tbshtMic: TTabSheet
        Caption = 'Mic'
        ImageIndex = 2
        DesignSize = (
          948
          264)
        object Label10: TLabel
          Left = 13
          Top = 48
          Width = 32
          Height = 13
          Caption = 'Device'
        end
        object pboxFreqCuts: TPaintBox
          Left = 3
          Top = 229
          Width = 381
          Height = 34
          Anchors = [akLeft, akBottom]
          OnMouseDown = pboxFreqCutsMouseDown
          OnMouseMove = pboxFreqCutsMouseMove
          OnMouseUp = pboxFreqCutsMouseUp
          OnPaint = pboxFreqCutsPaint
        end
        object comboboxAudioSources: TComboBox
          Left = 13
          Top = 64
          Width = 229
          Height = 21
          Style = csDropDownList
          TabOrder = 0
        end
        object Button27: TButton
          Left = 13
          Top = 16
          Width = 108
          Height = 25
          Action = actWaveStartListening
          TabOrder = 1
        end
        object Button28: TButton
          Left = 133
          Top = 16
          Width = 108
          Height = 25
          Action = actWaveStopListening
          TabOrder = 2
        end
        object pgctrlWaveViewer: TPageControl
          Left = 436
          Top = 10
          Width = 497
          Height = 246
          ActivePage = tbshtViewerFreq
          Anchors = [akLeft, akTop, akBottom]
          Constraints.MaxWidth = 640
          TabOrder = 3
          object tbshtViewerFreq: TTabSheet
            Caption = 'Frequency domain'
            object chartFreq: TChart
              Left = 0
              Top = 0
              Width = 489
              Height = 218
              AllowPanning = pmNone
              Title.Text.Strings = (
                'Freq (Hz)')
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.LogarithmicBase = 2.000000000000000000
              BottomAxis.Maximum = 11025.000000000000000000
              BottomAxis.Minimum = 60.000000000000000000
              LeftAxis.Automatic = False
              LeftAxis.AutomaticMaximum = False
              LeftAxis.AutomaticMinimum = False
              LeftAxis.LabelsSeparation = 20
              LeftAxis.Maximum = 10.000000000000000000
              LeftAxis.Minimum = -100.000000000000000000
              LeftAxis.Title.Caption = 'dB'
              LeftAxis.Title.Visible = False
              Panning.MouseWheel = pmwNone
              RightAxis.Visible = False
              View3D = False
              Zoom.Allow = False
              Align = alClient
              BevelOuter = bvNone
              ParentColor = True
              TabOrder = 0
              DefaultCanvas = 'TGDIPlusCanvas'
              ColorPaletteIndex = 13
              object SeriesFreqCuts: TAreaSeries
                Legend.Visible = False
                SeriesColor = 8454143
                ShowInLegend = False
                AreaChartBrush.Color = clGray
                AreaChartBrush.BackColor = clDefault
                ClickableLine = False
                DrawArea = True
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                Pointer.Visible = False
                Transparency = 72
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
                Data = {
                  0004000000000000000000000000000000000000000000000000000000000000
                  0000000000}
              end
              object SeriesFreq1: TLineSeries
                Legend.Visible = False
                SeriesColor = clBlue
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.Brush.Gradient.EndColor = 10708548
                Pointer.Gradient.EndColor = 10708548
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
              object SeriesFreq2: TLineSeries
                Legend.Visible = False
                Active = False
                SeriesColor = clBlue
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
              object SeriesdBThreshold: TLineSeries
                Legend.Visible = False
                SeriesColor = clRed
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
                Data = {000200000000000000000034C000000000000034C0}
              end
            end
          end
          object tbshtViewerTime: TTabSheet
            Caption = 'Time domain'
            ImageIndex = 1
            object chartTime: TChart
              Left = 0
              Top = 0
              Width = 489
              Height = 218
              Title.Text.Strings = (
                'Time (ms)')
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.LogarithmicBase = 2.000000000000000000
              BottomAxis.Maximum = 512.000000000000000000
              LeftAxis.Automatic = False
              LeftAxis.AutomaticMaximum = False
              LeftAxis.AutomaticMinimum = False
              LeftAxis.Maximum = 1.000000000000000000
              LeftAxis.Minimum = -1.000000000000000000
              RightAxis.Visible = False
              View3D = False
              Zoom.Allow = False
              Align = alClient
              BevelOuter = bvNone
              ParentColor = True
              TabOrder = 0
              DefaultCanvas = 'TGDIPlusCanvas'
              ColorPaletteIndex = 13
              object SeriesTime1: TLineSeries
                Legend.Visible = False
                SeriesColor = clBlue
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.Brush.Gradient.EndColor = 10708548
                Pointer.Gradient.EndColor = 10708548
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
                Data = {
                  001900000000000000007062400000000000205C400000000000001440000000
                  00006058400000000000A05E4000000000003066400000000000C04C40000000
                  0000605D40000000000000594000000000000059400000000000406A40000000
                  0000A0644000000000005069400000000000F064400000000000404F40000000
                  0000003E400000000000803B400000000000205C400000000000001E40000000
                  0000405A400000000000806B4000000000003071400000000000987740000000
                  0000707C400000000000987C40}
              end
              object SeriesTime2: TLineSeries
                Legend.Visible = False
                Active = False
                SeriesColor = clBlue
                ShowInLegend = False
                Brush.BackColor = clDefault
                ClickableLine = False
                Pointer.Brush.Gradient.EndColor = 10708548
                Pointer.Gradient.EndColor = 10708548
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
          end
        end
        object pnlThreshold: TPanel
          Left = 353
          Top = 63
          Width = 71
          Height = 167
          Anchors = [akLeft, akTop, akBottom]
          BevelOuter = bvNone
          Caption = 'pnlThreshold'
          ShowCaption = False
          TabOrder = 4
          object Label11: TLabel
            Left = 0
            Top = 0
            Width = 71
            Height = 13
            Align = alTop
            Alignment = taCenter
            Caption = 'Threshold'
            ExplicitWidth = 47
          end
          object lblThreshold: TLabel
            Left = 0
            Top = 13
            Width = 71
            Height = 13
            Align = alTop
            Alignment = taCenter
            AutoSize = False
            Caption = '-20 dB'
            ExplicitLeft = 9
            ExplicitTop = 28
            ExplicitWidth = 51
          end
          object Panel4: TPanel
            Left = 0
            Top = 26
            Width = 71
            Height = 141
            Align = alClient
            BevelOuter = bvNone
            Caption = 'Panel4'
            FullRepaint = False
            ShowCaption = False
            TabOrder = 0
            object pboxSpectrogramGradientIndicator: TPaintBox
              Left = 0
              Top = 0
              Width = 13
              Height = 141
              Align = alLeft
              OnMouseDown = pboxSpectrogramGradientIndicatorMouseDown
              OnMouseMove = pboxSpectrogramGradientIndicatorMouseMove
              OnMouseUp = pboxSpectrogramGradientIndicatorMouseUp
              OnPaint = pboxSpectrogramGradientIndicatorPaint
              ExplicitHeight = 174
            end
            object imgSpectrogramGradient: TImage
              AlignWithMargins = True
              Left = 15
              Top = 6
              Width = 17
              Height = 129
              Margins.Left = 2
              Margins.Top = 6
              Margins.Right = 2
              Margins.Bottom = 6
              Align = alLeft
              Stretch = True
              ExplicitHeight = 82
            end
            object Panel7: TPanel
              Left = 34
              Top = 0
              Width = 37
              Height = 141
              Align = alClient
              BevelOuter = bvNone
              Caption = 'Panel7'
              ShowCaption = False
              TabOrder = 0
              object Label13: TLabel
                Left = 0
                Top = 0
                Width = 37
                Height = 13
                Align = alTop
                Caption = '0dB'
                ExplicitWidth = 18
              end
              object lblFloor_dB: TLabel
                AlignWithMargins = True
                Left = 0
                Top = 127
                Width = 37
                Height = 13
                Margins.Left = 0
                Margins.Top = 0
                Margins.Right = 0
                Margins.Bottom = 1
                Align = alBottom
                Caption = '0dB'
                ExplicitWidth = 18
              end
            end
          end
        end
        object pnlSpectrogram: TPanel
          Left = 13
          Top = 96
          Width = 337
          Height = 129
          Anchors = [akLeft, akTop, akBottom]
          BevelKind = bkFlat
          BevelOuter = bvNone
          Caption = 'pnlSpectrogram'
          FullRepaint = False
          ShowCaption = False
          TabOrder = 5
          OnResize = pnlSpectrogramResize
          object pboxSpectrogram: TPaintBox
            Left = 34
            Top = 16
            Width = 256
            Height = 109
            Align = alClient
            OnPaint = pboxSpectrogramPaint
            ExplicitLeft = 46
            ExplicitTop = 17
            ExplicitWidth = 241
            ExplicitHeight = 111
          end
          object Panel2: TPanel
            Left = 0
            Top = 0
            Width = 333
            Height = 16
            Align = alTop
            BevelOuter = bvNone
            Caption = 'Spectrogram'
            TabOrder = 0
          end
          object pnlTime: TPanel
            AlignWithMargins = True
            Left = 291
            Top = 16
            Width = 42
            Height = 109
            Margins.Left = 1
            Margins.Top = 0
            Margins.Right = 0
            Margins.Bottom = 0
            Align = alRight
            BevelOuter = bvNone
            Caption = 'pnlTime'
            Color = clBlack
            ParentBackground = False
            ShowCaption = False
            TabOrder = 1
            object Label12: TLabel
              AlignWithMargins = True
              Left = 2
              Top = 93
              Width = 40
              Height = 13
              Margins.Left = 2
              Margins.Top = 0
              Margins.Right = 0
              Align = alBottom
              Caption = #8595'0 s'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clAqua
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              ExplicitWidth = 20
            end
            object lblSpectrogramDuration: TLabel
              AlignWithMargins = True
              Left = 2
              Top = 0
              Width = 40
              Height = 13
              Margins.Left = 2
              Margins.Top = 0
              Margins.Right = 0
              Align = alTop
              Caption = #8593'0 s'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clAqua
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              ExplicitWidth = 20
            end
          end
          object pnlPeaksTimepoint: TPanel
            AlignWithMargins = True
            Left = 0
            Top = 16
            Width = 33
            Height = 109
            Margins.Left = 0
            Margins.Top = 0
            Margins.Right = 1
            Margins.Bottom = 0
            Align = alLeft
            BevelOuter = bvNone
            Caption = 'pnlPeaksTimepoint'
            Color = clNavy
            FullRepaint = False
            ParentBackground = False
            ShowCaption = False
            TabOrder = 2
            object pboxPeaksTimepoint: TPaintBox
              Left = 0
              Top = 0
              Width = 33
              Height = 109
              Align = alClient
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -9
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              OnPaint = pboxPeaksTimepointPaint
              ExplicitWidth = 28
            end
          end
        end
        object Button29: TButton
          Left = 253
          Top = 16
          Width = 108
          Height = 25
          Action = actWaveSetParameters
          TabOrder = 6
        end
      end
    end
  end
  object ActionManager1: TActionManager
    OnExecute = ActionManager1Execute
    OnUpdate = ActionManager1Update
    Left = 432
    Top = 320
    StyleName = 'Platform Default'
    object actGareProssimaPA4: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prossima serie PA 4"'
      OnExecute = actGareProssimaPA4Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPS10: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prossima serie PS 10"'
      OnExecute = actGareProssimaPS10Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPA8: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prima serie PA 8"'
      OnExecute = actGarePrimaPA8Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPA6: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prossima serie PA 6"'
      OnExecute = actGareProssimaPA6Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProvaPGCMiratoStart: TAction
      Category = 'GarePGCMirato'
      Caption = 'Serie di prova PGC Mirato'
      Hint = 'Serie di prova PGC Mirato|Chiuso per 7" e poi aperto per 300"'
      OnExecute = actGareProvaPGCMiratoStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPA8: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prossima serie PA 8"'
      OnExecute = actGareProssimaPA8Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPS20: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prossima serie PS 20"'
      OnExecute = actGareProssimaPS20Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPGCMiratoStart: TAction
      Category = 'GarePGCMirato'
      Caption = 'Prossima serie PGC Mirato'
      Hint = 'Prossima serie  PGC Mirato|Chiuso per 7" e poi aperto per 300"'
      OnExecute = actGareProssimaPGCMiratoStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPS150: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prima serie PS 150"'
      OnExecute = actGarePrimaPS150Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPS150: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prossima serie PS 150"'
      OnExecute = actGareProssimaPS150Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPGCCelereStart: TAction
      Category = 'GarePGCCelere'
      Caption = 'Prima serie PGC Celere'
      Hint = 
        'Prima serie PGC Celere|Chiuso per 7" e poi aperto per 5" per 5 v' +
        'olte'
      OnExecute = actGarePrimaPGCCelereStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProssimaPGCCelereStart: TAction
      Category = 'GarePGCCelere'
      Caption = 'Prossima serie PGC Celere'
      Hint = 
        'Prossima serie PGC Celere|Chiuso per 7" e poi aperto per 5" per ' +
        '5 volte'
      OnExecute = actGareProssimaPGCCelereStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actOpen: TAction
      Caption = 'Open'
      OnExecute = actOpenExecute
      OnUpdate = EnableIfConnectionIsClose
    end
    object actFnReadHoldingRegisters: TAction
      Category = 'Modbus'
      Caption = 'Read Holding Regs'
      OnExecute = actFnReadHoldingRegistersExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actFnReadInputRegisters: TAction
      Category = 'Modbus'
      Caption = 'Read Input Regs'
      OnExecute = actFnReadInputRegistersExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGareProvaPA8: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Serie di prova PA 8"'
      OnExecute = actGareProvaPA8Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPA6: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prima serie PA 6"'
      OnExecute = actGarePrimaPA6Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actFnPresetSingleRegister: TAction
      Category = 'Modbus'
      Caption = 'Preset Single Reg'
      OnExecute = actFnPresetSingleRegisterExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actFnPresetMultipleRegisters: TAction
      Category = 'Modbus'
      Caption = 'Preset Multiple Regs'
      OnExecute = actFnPresetMultipleRegistersExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGarePrimaPA4: TAction
      Category = 'GarePistolaAutomatica'
      Caption = 'Prima serie PA 4"'
      OnExecute = actGarePrimaPA4Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actClose: TAction
      Caption = 'Close'
      OnExecute = actCloseExecute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGarePrimaPGCMiratoStart: TAction
      Category = 'GarePGCMirato'
      Caption = 'Prima serie PGC Mirato'
      Hint = 'Prima serie PGC Mirato|Chiuso per 7" e poi aperto per 300"'
      OnExecute = actGarePrimaPGCMiratoStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareResetCycle: TAction
      Category = 'Gare'
      Caption = 'Reset'
      Hint = 'Reset sagome|Ciclo di reset delle sagome'
      OnExecute = actGareResetCycleExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareStop: TAction
      Category = 'Gare'
      Caption = 'Stop'
      OnExecute = actGareStopExecute
      OnUpdate = EnabledIfTrialIsRunning
    end
    object actGarePrimaPS10: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prima serie PS 10"'
      OnExecute = actGarePrimaPS10Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareProvaPGCCelereStart: TAction
      Category = 'GarePGCCelere'
      Caption = 'Serie di prova PGC Celere'
      Hint = 
        'Serie di prova PGC Celere|Chiuso per 7" e poi aperto per 5" per ' +
        '5 volte'
      OnExecute = actGareProvaPGCCelereStartExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareApertura: TAction
      Category = 'Gare'
      Caption = 'Apertura'
      Hint = 'Apertura|Apertura manuale sagome'
      OnExecute = actGareAperturaExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareChiusura: TAction
      Category = 'Gare'
      Caption = 'Chiusura'
      Hint = 'Chiusura|Chiusura manuale sagome'
      OnExecute = actGareChiusuraExecute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGareEnb1_5: TAction
      Category = 'Gare'
      AutoCheck = True
      Caption = 'Abilitazione 1-5'
      Hint = 'Abilitazione sagome dalla 1 alla 5'
      OnExecute = actGareEnb1_5Execute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGareEnb6_10: TAction
      Category = 'Gare'
      AutoCheck = True
      Caption = 'Abilitazione 6-10'
      Hint = 'Abilitazione sagome dalla 6 alla 10'
      OnExecute = actGareEnb6_10Execute
      OnUpdate = EnableIfConnectionIsOpen
    end
    object actGareProvaPS150: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Serie di prova PS 150"'
      OnExecute = actGareProvaPS150Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actGarePrimaPS20: TAction
      Category = 'GarePistolaStandard'
      Caption = 'Prima serie PS 20"'
      OnExecute = actGarePrimaPS20Execute
      OnUpdate = EnableIfConnectionIsOpenAndEnabled
    end
    object actWaveStartListening: TAction
      Category = 'Wave'
      Caption = 'Start listening'
      OnExecute = actWaveStartListeningExecute
      OnUpdate = actWaveStartListeningUpdate
    end
    object actWaveStopListening: TAction
      Category = 'Wave'
      Caption = 'Stop listening'
      OnExecute = actWaveStopListeningExecute
      OnUpdate = actWaveStopListeningUpdate
    end
    object actWaveSetParameters: TAction
      Category = 'Wave'
      Caption = 'Set parameters...'
      OnExecute = actWaveSetParametersExecute
      OnUpdate = actWaveSetParametersUpdate
    end
    object actViewSetUIModeLight: TAction
      Category = 'View'
      Caption = 'Tema &chiaro'
      Hint = 'Imposta tema chiaro'
      OnExecute = actViewSetUIModeLightExecute
      OnUpdate = actViewSetUIModeLightUpdate
    end
    object actViewSetUIModeDark: TAction
      Category = 'View'
      Caption = 'Tema &scuro'
      Hint = 'Imposta tema scuro'
      OnExecute = actViewSetUIModeDarkExecute
      OnUpdate = actViewSetUIModeDarkUpdate
    end
    object actViewToggleUIMode: TAction
      Category = 'View'
      Caption = 'Cambia tema'
      Hint = 'Cambia tema|Passa al tema successivo'
      OnExecute = actViewToggleUIModeExecute
    end
  end
  object ApplicationEvents1: TApplicationEvents
    OnActivate = ApplicationEvents1Activate
    OnDeactivate = ApplicationEvents1Deactivate
    OnIdle = ApplicationEvents1Idle
    Left = 480
    Top = 360
  end
  object tmrGare: TTimer
    Enabled = False
    Interval = 20
    OnTimer = tmrGareTimer
    Left = 292
    Top = 399
  end
  object tmrReadStatusPorta: TTimer
    Enabled = False
    OnTimer = tmrReadStatusPortaTimer
    Left = 364
    Top = 468
  end
  object SVGIcnImgCollTitleBar: TSVGIconImageCollection
    SVGIconItems = <
      item
        IconName = 'DarkMode'
        SVGText = 
          '<?xml version="1.0" standalone="no"?>'#13#10'<svg xml:space="preserve"' +
          ' width="75.999329" height="76.464935" version="1.1" shape-render' +
          'ing="geometricPrecision" text-rendering="geometricPrecision" ima' +
          'ge-rendering="optimizeQuality" fill-rule="evenodd" clip-rule="ev' +
          'enodd" viewBox="0 0 88.23922 88.163077" id="svg204" sodipodi:doc' +
          'name="DarkMode.svg" inkscape:version="1.2.2 (b0a8486541, 2022-12' +
          '-01)" xmlns:inkscape="http://www.inkscape.org/namespaces/inkscap' +
          'e" xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-' +
          '0.dtd" xmlns="http://www.w3.org/2000/svg" xmlns:svg="http://www.' +
          'w3.org/2000/svg">'#13#10'  <defs id="defs208"/>'#13#10'  <sodipodi:namedview' +
          ' id="namedview206" pagecolor="#ffffff" bordercolor="#666666" bor' +
          'deropacity="1.0" inkscape:showpageshadow="2" inkscape:pageopacit' +
          'y="0.0" inkscape:pagecheckerboard="0" inkscape:deskcolor="#d1d1d' +
          '1" showgrid="false" inkscape:zoom="11.25974" inkscape:cx="37.967' +
          '128" inkscape:cy="38.233564" inkscape:window-width="1920" inksca' +
          'pe:window-height="1115" inkscape:window-x="0" inkscape:window-y=' +
          '"0" inkscape:window-maximized="1" inkscape:current-layer="svg204' +
          '"/>'#13#10#13#10'   <g id="Livello_x0020_1" inkscape:label="Livello 1" ink' +
          'scape:groupmode="layer" transform="translate(0,-0.31071204)">'#13#10' ' +
          '   <metadata id="CorelCorpID_0Corel-Layer"/>'#13#10'  '#13#10'    <path fill' +
          '="#373435" d="m 84.16,41.85 3.83,-4.59 C 90.54,64.85 73.35,88.78' +
          ' 44.29,88.78 19.83,88.78 0,68.94 0,44.48 0,17.98 25,-4.52 51.52,' +
          '0.78 l -4.59,3.83 c -9.86,10.32 -9.72,26.67 0.42,36.81 10.14,10.' +
          '14 26.5,10.29 36.81,0.43 z M 41.26,4.64 c -8.84,12 -7.83,28.98 3' +
          '.03,39.84 10.86,10.86 27.85,11.87 39.85,3.03 C 82.59,68.17 65.34' +
          ',84.44 44.29,84.44 22.22,84.44 4.33,66.55 4.33,44.48 4.33,23.43 ' +
          '20.61,6.19 41.26,4.64 Z" id="path201"/>'#13#10'  '#13#10' </g>'#13#10#13#10'</svg>'#13#10
      end
      item
        IconName = 'LightMode'
        SVGText = 
          '<?xml version="1.0" standalone="no"?>'#13#10'<svg xml:space="preserve"' +
          ' width="75" height="75" version="1.1" shape-rendering="geometric' +
          'Precision" text-rendering="geometricPrecision" image-rendering="' +
          'optimizeQuality" fill-rule="evenodd" clip-rule="evenodd" viewBox' +
          '="0 0 87.7 87.7" id="svg264" sodipodi:docname="LightMode.svg" in' +
          'kscape:version="1.2.2 (b0a8486541, 2022-12-01)" xmlns:inkscape="' +
          'http://www.inkscape.org/namespaces/inkscape" xmlns:sodipodi="htt' +
          'p://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd" xmlns="http://w' +
          'ww.w3.org/2000/svg" xmlns:svg="http://www.w3.org/2000/svg">'#13#10'  <' +
          'defs id="defs268"/>'#13#10'  <sodipodi:namedview id="namedview266" pag' +
          'ecolor="#ffffff" bordercolor="#666666" borderopacity="1.0" inksc' +
          'ape:showpageshadow="2" inkscape:pageopacity="0.0" inkscape:pagec' +
          'heckerboard="0" inkscape:deskcolor="#d1d1d1" showgrid="false" in' +
          'kscape:zoom="3.1466667" inkscape:cx="37.658898" inkscape:cy="37.' +
          '658898" inkscape:window-width="1920" inkscape:window-height="111' +
          '5" inkscape:window-x="0" inkscape:window-y="0" inkscape:window-m' +
          'aximized="1" inkscape:current-layer="Livello_x0020_1"/>'#13#10#13#10'   <g' +
          ' id="Livello_x0020_1" inkscape:label="Livello 1" inkscape:groupm' +
          'ode="layer">'#13#10'    <metadata id="CorelCorpID_0Corel-Layer"/>'#13#10'  '#13 +
          #10'    <path fill="#373435" d="M 69.23,41.67 H 87.7 v 4.37 H 69.23' +
          ' c 0.06,-0.72 0.1,-1.45 0.1,-2.19 0,-0.73 -0.04,-1.46 -0.1,-2.18' +
          ' z M 0,41.67 h 18.47 c -0.06,0.72 -0.09,1.45 -0.09,2.18 0,0.74 0' +
          '.03,1.47 0.09,2.19 H 0 Z M 60.25,24.36 73.32,11.3 76.4,14.39 63.' +
          '34,27.45 C 62.4,26.33 61.37,25.3 60.25,24.36 Z M 11.3,73.32 24.3' +
          '6,60.25 c 0.94,1.12 1.97,2.15 3.09,3.09 L 14.39,76.4 Z M 41.67,1' +
          '8.47 V 0 h 4.36 v 18.47 c -0.72,-0.06 -1.44,-0.09 -2.18,-0.09 -0' +
          '.73,0 -1.46,0.03 -2.18,0.09 z m 0,69.23 V 69.23 c 0.72,0.06 1.45' +
          ',0.1 2.18,0.1 0.74,0 1.46,-0.04 2.18,-0.1 V 87.7 Z M 24.36,27.45' +
          ' 11.3,14.39 14.39,11.3 27.45,24.36 c -1.12,0.94 -2.15,1.97 -3.09' +
          ',3.09 z M 73.31,76.4 60.25,63.34 c 1.12,-0.94 2.15,-1.97 3.09,-3' +
          '.09 L 76.4,73.31 Z M 43.85,25.43 c 10.18,0 18.43,8.25 18.43,18.4' +
          '2 0,10.18 -8.25,18.43 -18.43,18.43 -10.17,0 -18.42,-8.25 -18.42,' +
          '-18.43 0,-10.17 8.25,-18.42 18.42,-18.42 z m 0,4.32 c 7.79,0 14.' +
          '11,6.31 14.11,14.1 0,7.79 -6.32,14.11 -14.11,14.11 -7.79,0 -14.1' +
          ',-6.32 -14.1,-14.11 0,-7.79 6.31,-14.1 14.1,-14.1 z" id="path261' +
          '"/>'#13#10'  '#13#10' </g>'#13#10#13#10'</svg>'#13#10
      end
      item
        IconName = 'DarkModeBold'
        SVGText = 
          '<?xml version="1.0" encoding="UTF-8" standalone="no"?>'#10'<svg'#10'   x' +
          'ml:space="preserve"'#10'   width="75.999329"'#10'   height="76.464935"'#10' ' +
          '  version="1.1"'#10'   viewBox="0 0 88.23922 88.163077"'#10'   xmlns="ht' +
          'tp://www.w3.org/2000/svg"><path'#10'   fill="#373435"'#10'   d="m 84.16,' +
          '41.85 3.83,-4.59 C 90.54,64.85 73.35,88.78 44.29,88.78 19.83,88.' +
          '78 0,68.94 0,44.48 0,17.98 25,-4.52 51.52,0.78 l -4.59,3.83 c -9' +
          '.86,10.32 -9.72,26.67 0.42,36.81 10.14,10.14 26.5,10.29 36.81,0.' +
          '43 z M 34.05,9.65 C 19.44,14.18 8.18,28.57 8.18,44.48 8.18,64.43' +
          ' 24.34,80.6 44.29,80.6 62.05,80.6 74.11,69.84 78.37,55.02 66.01,' +
          '59.77 51.5,57.13 41.57,47.21 31.44,37.07 28.9,22.17 34.05,9.65 Z' +
          '" /></svg>'#10
      end
      item
        IconName = 'LightModeBold'
        SVGText = 
          '<?xml version="1.0" encoding="UTF-8" standalone="no"?>'#10'<svg'#10'   x' +
          'ml:space="preserve"'#10'   width="80"'#10'   height="80"'#10'   version="1.1' +
          '"'#10'   viewBox="0 0 92.62 92.62"'#10'   xmlns="http://www.w3.org/2000/' +
          'svg"><path'#10'   fill="#373435"'#10'   d="m 46.31,35.1 c 6.2,0 11.22,5.' +
          '02 11.22,11.21 0,6.2 -5.02,11.22 -11.22,11.22 -6.19,0 -11.21,-5.' +
          '02 -11.21,-11.22 0,-6.19 5.02,-11.21 11.21,-11.21 z m 0,-7.1 c 1' +
          '0.12,0 18.31,8.2 18.31,18.31 0,10.12 -8.19,18.31 -18.31,18.31 C ' +
          '36.2,64.62 28,56.43 28,46.31 28,36.2 36.2,28 46.31,28 Z M 73.66,' +
          '80.59 60.68,67.61 c -0.56,-0.56 -0.83,-1.25 -0.8,-2.04 0.04,-0.8' +
          ' 0.36,-1.47 0.97,-1.98 0.99,-0.83 1.91,-1.75 2.74,-2.74 0.51,-0.' +
          '61 1.18,-0.93 1.98,-0.97 0.79,-0.03 1.48,0.24 2.04,0.8 l 12.98,1' +
          '2.98 c 1.07,1.06 1.07,2.8 0,3.86 l -3.07,3.07 c -1.06,1.07 -2.8,' +
          '1.07 -3.86,0 z M 25.01,31.94 12.03,18.96 c -1.07,-1.06 -1.07,-2.' +
          '8 0,-3.86 l 3.07,-3.07 c 1.06,-1.07 2.8,-1.07 3.86,0 l 12.98,12.' +
          '98 c 0.57,0.56 0.84,1.26 0.8,2.05 -0.03,0.79 -0.36,1.46 -0.97,1.' +
          '97 -0.99,0.84 -1.9,1.75 -2.74,2.74 -0.51,0.61 -1.18,0.94 -1.97,0' +
          '.97 -0.79,0.04 -1.49,-0.23 -2.05,-0.8 z m 16.4,57.95 V 71.53 c 0' +
          ',-0.79 0.3,-1.47 0.88,-2.01 0.58,-0.54 1.29,-0.78 2.08,-0.71 0.6' +
          '5,0.05 1.29,0.08 1.94,0.08 0.65,0 1.3,-0.03 1.94,-0.08 0.79,-0.0' +
          '7 1.5,0.17 2.08,0.71 0.59,0.54 0.88,1.22 0.88,2.01 v 18.36 c 0,1' +
          '.51 -1.22,2.73 -2.73,2.73 h -4.34 c -1.5,0 -2.73,-1.22 -2.73,-2.' +
          '73 z m 0,-68.8 V 2.73 C 41.41,1.23 42.64,0 44.14,0 h 4.34 c 1.51' +
          ',0 2.73,1.23 2.73,2.73 v 18.36 c 0,0.79 -0.29,1.48 -0.88,2.01 -0' +
          '.58,0.54 -1.29,0.78 -2.08,0.71 -0.64,-0.05 -1.29,-0.08 -1.94,-0.' +
          '08 -0.65,0 -1.29,0.03 -1.94,0.08 -0.79,0.07 -1.5,-0.17 -2.08,-0.' +
          '71 -0.58,-0.53 -0.88,-1.22 -0.88,-2.01 z M 12.03,73.66 25.01,60.' +
          '68 c 0.56,-0.56 1.26,-0.83 2.05,-0.8 0.79,0.04 1.46,0.36 1.97,0.' +
          '97 0.84,0.99 1.75,1.91 2.74,2.74 0.61,0.51 0.94,1.18 0.97,1.98 0' +
          '.04,0.79 -0.23,1.48 -0.8,2.04 L 18.96,80.59 c -1.06,1.07 -2.8,1.' +
          '07 -3.86,0 l -3.07,-3.07 c -1.06,-1.06 -1.06,-2.8 0,-3.86 z M 60' +
          '.68,25.01 73.66,12.03 c 1.06,-1.06 2.8,-1.06 3.86,0 l 3.07,3.07 ' +
          'c 1.07,1.06 1.07,2.8 0,3.86 L 67.61,31.94 c -0.56,0.57 -1.25,0.8' +
          '4 -2.04,0.8 -0.8,-0.03 -1.47,-0.36 -1.98,-0.97 -0.83,-0.99 -1.75' +
          ',-1.9 -2.74,-2.74 -0.61,-0.51 -0.93,-1.18 -0.97,-1.97 -0.03,-0.7' +
          '9 0.24,-1.49 0.8,-2.05 z M 2.73,41.41 h 18.36 c 0.79,0 1.48,0.3 ' +
          '2.01,0.88 0.54,0.59 0.78,1.29 0.71,2.08 -0.05,0.65 -0.08,1.29 -0' +
          '.08,1.94 0,0.65 0.03,1.3 0.08,1.94 0.07,0.79 -0.17,1.5 -0.71,2.0' +
          '8 -0.53,0.59 -1.22,0.89 -2.01,0.89 H 2.73 C 1.23,51.22 0,49.99 0' +
          ',48.48 v -4.34 c 0,-1.5 1.23,-2.73 2.73,-2.73 z m 68.8,0 h 18.36' +
          ' c 1.51,0 2.73,1.23 2.73,2.73 v 4.34 c 0,1.51 -1.22,2.74 -2.73,2' +
          '.74 H 71.53 c -0.79,0 -1.47,-0.3 -2.01,-0.89 -0.54,-0.58 -0.78,-' +
          '1.29 -0.71,-2.08 0.05,-0.64 0.08,-1.29 0.08,-1.94 0,-0.65 -0.03,' +
          '-1.29 -0.08,-1.94 -0.07,-0.79 0.17,-1.49 0.71,-2.08 0.54,-0.58 1' +
          '.22,-0.88 2.01,-0.88 z" /></svg>'#10
      end
      item
        IconName = 'DarkModeSemiBold'
        SVGText = 
          '<?xml version="1.0" encoding="UTF-8" standalone="no"?>'#10'<svg'#10'   x' +
          'ml:space="preserve"'#10'   width="75.004623"'#10'   height="75.465355"'#10' ' +
          '  version="1.1"'#10'   viewBox="0 0 87.305382 87.222063"'#10'   xmlns="h' +
          'ttp://www.w3.org/2000/svg"><path'#10'   fill="#373435"'#10'   d="M 49.52' +
          ',0.51 C 23.85,-3.66 0,18.27 0,44.01 c 0,24.21 19.62,43.83 43.82,' +
          '43.83 28.07,0 45.06,-22.71 43.37,-49.36 l -2.83,3.38 C 73.7,52.0' +
          '5 56.84,51.85 46.41,41.42 35.99,31 35.79,14.14 46.03,3.43 Z M 34' +
          '.17,9.28 c -5.22,12.67 -2.31,27.27 7.4,36.99 9.51,9.51 23.72,12.' +
          '5 36.25,7.7 l 1.28,-0.5 -0.38,1.32 C 74.03,71.12 60.81,80.99 43.' +
          '82,80.99 23.4,80.99 6.85,64.44 6.85,44.01 6.85,28 18.09,13.09 33' +
          '.33,8.36 l 1.39,-0.43 z" /></svg>'#10
      end
      item
        IconName = 'LightModeSemiBold'
        SVGText = 
          '<?xml version="1.0" encoding="UTF-8" standalone="no"?>'#10'<svg'#10'   x' +
          'ml:space="preserve"'#10'   width="79"'#10'   height="79"'#10'   version="1.1' +
          '"'#10'   viewBox="0 0 91.68 91.68"'#10'   xmlns="http://www.w3.org/2000/' +
          'svg"><path'#10'   fill="#373435"'#10'   d="m 71.18,41.6 c -0.6,0 -1.11,0' +
          '.22 -1.51,0.67 -0.41,0.44 -0.59,0.96 -0.54,1.57 0.05,0.66 0.09,1' +
          '.33 0.09,2 0,0.67 -0.04,1.34 -0.09,2.01 -0.05,0.6 0.13,1.12 0.54' +
          ',1.57 0.4,0.44 0.91,0.66 1.51,0.66 h 18.44 c 1.14,0 2.06,-0.92 2' +
          '.06,-2.06 v -4.36 c 0,-1.13 -0.92,-2.06 -2.06,-2.06 z m 2.62,38.' +
          '2 c 0.8,0.8 2.11,0.8 2.91,0 l 3.09,-3.09 c 0.8,-0.8 0.8,-2.11 0,' +
          '-2.91 L 66.76,60.76 c -0.43,-0.42 -0.95,-0.62 -1.55,-0.6 -0.6,0.' +
          '03 -1.09,0.27 -1.48,0.73 -0.87,1.02 -1.82,1.97 -2.84,2.84 -0.46,' +
          '0.39 -0.7,0.88 -0.73,1.48 -0.02,0.6 0.18,1.12 0.6,1.55 z m -32.2' +
          ',9.82 c 0,1.14 0.93,2.06 2.06,2.06 h 4.36 c 1.13,0 2.06,-0.92 2.' +
          '06,-2.06 V 71.18 c 0,-0.6 -0.22,-1.11 -0.66,-1.51 -0.45,-0.41 -0' +
          '.97,-0.59 -1.57,-0.54 -0.67,0.05 -1.34,0.09 -2.01,0.09 -0.67,0 -' +
          '1.34,-0.04 -2.01,-0.09 -0.6,-0.05 -1.12,0.13 -1.56,0.54 -0.45,0.' +
          '4 -0.67,0.91 -0.67,1.51 z M 11.89,73.8 c -0.81,0.8 -0.81,2.11 0,' +
          '2.91 l 3.08,3.09 c 0.8,0.8 2.11,0.8 2.91,0 L 30.92,66.76 c 0.43,' +
          '-0.43 0.63,-0.95 0.6,-1.55 -0.02,-0.6 -0.26,-1.09 -0.73,-1.48 -1' +
          '.02,-0.87 -1.97,-1.82 -2.83,-2.84 -0.39,-0.46 -0.89,-0.7 -1.49,-' +
          '0.73 -0.6,-0.02 -1.12,0.18 -1.54,0.6 z M 2.06,41.6 C 0.93,41.6 0' +
          ',42.53 0,43.66 v 4.36 c 0,1.14 0.93,2.06 2.06,2.06 H 20.5 c 0.61' +
          ',0 1.11,-0.22 1.52,-0.66 0.41,-0.45 0.59,-0.97 0.53,-1.57 -0.05,' +
          '-0.67 -0.08,-1.34 -0.08,-2.01 0,-0.67 0.03,-1.34 0.08,-2 0.06,-0' +
          '.61 -0.12,-1.13 -0.53,-1.57 C 21.61,41.82 21.11,41.6 20.5,41.6 Z' +
          ' M 24.93,30.92 c 0.42,0.43 0.94,0.63 1.54,0.6 0.6,-0.02 1.1,-0.2' +
          '6 1.49,-0.73 0.86,-1.02 1.81,-1.97 2.83,-2.83 0.47,-0.39 0.71,-0' +
          '.89 0.73,-1.49 0.03,-0.6 -0.17,-1.12 -0.6,-1.54 L 17.88,11.89 c ' +
          '-0.8,-0.81 -2.11,-0.81 -2.91,0 l -3.08,3.08 c -0.81,0.8 -0.81,2.' +
          '11 0,2.91 z M 41.6,20.5 c 0,0.61 0.22,1.11 0.67,1.52 0.44,0.41 0' +
          '.96,0.59 1.56,0.53 0.67,-0.05 1.34,-0.08 2.01,-0.08 0.67,0 1.34,' +
          '0.03 2.01,0.08 0.6,0.06 1.12,-0.12 1.57,-0.53 0.44,-0.41 0.66,-0' +
          '.91 0.66,-1.52 V 2.06 C 50.08,0.93 49.15,0 48.02,0 H 43.66 C 42.' +
          '53,0 41.6,0.93 41.6,2.06 Z m 19.16,4.43 c -0.42,0.42 -0.62,0.94 ' +
          '-0.6,1.54 0.03,0.6 0.27,1.1 0.73,1.49 1.02,0.86 1.97,1.81 2.84,2' +
          '.83 0.39,0.47 0.88,0.71 1.48,0.73 0.6,0.03 1.12,-0.17 1.55,-0.6 ' +
          'L 79.8,17.88 c 0.8,-0.8 0.8,-2.11 0,-2.91 l -3.09,-3.08 c -0.8,-' +
          '0.81 -2.11,-0.81 -2.91,0 z m -14.92,3.2 c -9.78,0 -17.71,7.93 -1' +
          '7.71,17.71 0,9.78 7.93,17.71 17.71,17.71 9.78,0 17.71,-7.93 17.7' +
          '1,-17.71 0,-9.78 -7.93,-17.71 -17.71,-17.71 z m 0,5.76 c 6.6,0 1' +
          '1.95,5.35 11.95,11.95 0,6.6 -5.35,11.95 -11.95,11.95 -6.6,0 -11.' +
          '95,-5.35 -11.95,-11.95 0,-6.6 5.35,-11.95 11.95,-11.95 z" /></sv' +
          'g>'#10
      end
      item
        IconName = 'AutoMode'
        SVGText = 
          '<?xml version="1.0" encoding="UTF-8" standalone="no"?><svg xmlns' +
          '="http://www.w3.org/2000/svg" viewBox="0 0 80 80"><circle cx="40' +
          '" cy="40" r="32" fill="none" stroke="#373435" stroke-width="6"/>' +
          '<path fill="#373435" d="M40 8 A32 32 0 0 1 40 72 Z"/></svg>'
      end>
    Left = 472
    Top = 328
  end
  object SVGIcnVirtImgListTitleBar: TSVGIconVirtualImageList
    Images = <
      item
        CollectionIndex = 0
        CollectionName = 'DarkMode'
        Name = 'DarkMode'
      end
      item
        CollectionIndex = 1
        CollectionName = 'LightMode'
        Name = 'LightMode'
      end
      item
        CollectionIndex = 2
        CollectionName = 'DarkModeBold'
        Name = 'DarkModeBold'
      end
      item
        CollectionIndex = 3
        CollectionName = 'LightModeBold'
        Name = 'LightModeBold'
      end
      item
        CollectionIndex = 4
        CollectionName = 'DarkModeSemiBold'
        Name = 'DarkModeSemiBold'
      end
      item
        CollectionIndex = 5
        CollectionName = 'LightModeSemiBold'
        Name = 'LightModeSemiBold'
      end
      item
        CollectionIndex = 6
        CollectionName = 'AutoMode'
        Name = 'AutoMode'
      end>
    ImageCollection = SVGIcnImgCollTitleBar
    Left = 480
    Top = 264
  end
end
